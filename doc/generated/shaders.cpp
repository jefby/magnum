/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <Corrade/PluginManager/Manager.h>
#include <Corrade/Utility/Directory.h>

#ifdef CORRADE_TARGET_APPLE
#include <Magnum/Platform/WindowlessCglApplication.h>
#elif defined(CORRADE_TARGET_UNIX)
#include <Magnum/Platform/WindowlessGlxApplication.h>
#elif defined(CORRADE_TARGET_WINDOWS)
#include <Magnum/Platform/WindowlessWglApplication.h>
#else
#error no windowless application available on this platform
#endif

#include <Magnum/Image.h>
#include <Magnum/PixelFormat.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/Framebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderbuffer.h>
#include <Magnum/GL/RenderbufferFormat.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/TextureFormat.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/Primitives/Square.h>
#include <Magnum/Primitives/Circle.h>
#include <Magnum/Primitives/Icosphere.h>
#include <Magnum/Primitives/UVSphere.h>
#include <Magnum/Shaders/Flat.h>
#include <Magnum/Shaders/MeshVisualizer.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Shaders/VertexColor.h>
#include <Magnum/Shaders/Vector.h>
#include <Magnum/Shaders/DistanceFieldVector.h>
#include <Magnum/Trade/AbstractImageConverter.h>
#include <Magnum/Trade/ImageData.h>
#include <Magnum/Trade/MeshData2D.h>
#include <Magnum/Trade/MeshData3D.h>
#include <Magnum/Trade/AbstractImporter.h>

using namespace Magnum;
using namespace Magnum::Math::Literals;

struct ShaderVisualizer: Platform::WindowlessApplication {
    explicit ShaderVisualizer(const Arguments& arguments): Platform::WindowlessApplication{arguments} {}

    int exec() override;

    std::string phong();
    std::string meshVisualizer();
    std::string flat();
    std::string vertexColor();

    std::string vector();
    std::string distanceFieldVector();

    std::unique_ptr<Trade::AbstractImporter> _importer;
};

namespace {
    constexpr const Vector2i ImageSize{256};
}

int ShaderVisualizer::exec() {
    PluginManager::Manager<Trade::AbstractImageConverter> converterManager;
    std::unique_ptr<Trade::AbstractImageConverter> converter = converterManager.loadAndInstantiate("PngImageConverter");
    if(!converter) {
        Error() << "Cannot load image converter plugin";
        std::exit(1);
    }

    PluginManager::Manager<Trade::AbstractImporter> importerManager;
    _importer = importerManager.loadAndInstantiate("PngImporter");
    if(!_importer) {
        Error() << "Cannot load image importer plugin";
        std::exit(1);
    }

    GL::Renderbuffer multisampleColor, multisampleDepth;
    multisampleColor.setStorageMultisample(16, GL::RenderbufferFormat::RGBA8, ImageSize);
    multisampleDepth.setStorageMultisample(16, GL::RenderbufferFormat::DepthComponent24, ImageSize);

    GL::Framebuffer multisampleFramebuffer{{{}, ImageSize}};
    multisampleFramebuffer.attachRenderbuffer(GL::Framebuffer::ColorAttachment{0}, multisampleColor)
        .attachRenderbuffer(GL::Framebuffer::BufferAttachment::Depth, multisampleDepth)
        .bind();
    CORRADE_INTERNAL_ASSERT(multisampleFramebuffer.checkStatus(GL::FramebufferTarget::Draw) == GL::Framebuffer::Status::Complete);

    GL::Renderbuffer color;
    color.setStorage(GL::RenderbufferFormat::RGBA8, ImageSize);
    GL::Framebuffer framebuffer{{{}, ImageSize}};
    framebuffer.attachRenderbuffer(GL::Framebuffer::ColorAttachment{0}, color);

    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::setClearColor(0x000000_rgbaf);

    for(auto fun: {&ShaderVisualizer::phong,
                   &ShaderVisualizer::meshVisualizer,
                   &ShaderVisualizer::flat,
                   &ShaderVisualizer::vertexColor,
                   &ShaderVisualizer::vector,
                   &ShaderVisualizer::distanceFieldVector}) {
        multisampleFramebuffer.clear(GL::FramebufferClear::Color|GL::FramebufferClear::Depth);

        std::string filename = (this->*fun)();

        GL::AbstractFramebuffer::blit(multisampleFramebuffer, framebuffer, framebuffer.viewport(), GL::FramebufferBlit::Color);
        Image2D result = framebuffer.read(framebuffer.viewport(), {PixelFormat::RGBA8Unorm});
        converter->exportToFile(result, Utility::Directory::join("../", "shaders-" + filename));
    }

    _importer.reset();

    return 0;
}

namespace {
    const auto Projection = Matrix4::perspectiveProjection(35.0_degf, 1.0f, 0.001f, 100.0f);
    const auto Transformation = Matrix4::translation(Vector3::zAxis(-5.0f));
    const auto BaseColor = 0x2f83cc_rgbf;
    const auto OutlineColor = 0xdcdcdc_rgbf;
}

std::string ShaderVisualizer::phong() {
    std::unique_ptr<GL::Buffer> vertices, indices;
    GL::Mesh mesh{NoCreate};
    std::tie(mesh, vertices, indices) = MeshTools::compile(Primitives::uvSphereSolid(16, 32), GL::BufferUsage::StaticDraw);

    Shaders::Phong shader;
    shader.setAmbientColor(0x22272e_rgbf)
        .setDiffuseColor(BaseColor)
        .setShininess(200.0f)
        .setLightPosition({5.0f, 5.0f, 7.0f})
        .setProjectionMatrix(Projection)
        .setTransformationMatrix(Transformation)
        .setNormalMatrix(Transformation.rotationScaling());

    mesh.draw(shader);

    return "phong.png";
}

std::string ShaderVisualizer::meshVisualizer() {
    std::unique_ptr<GL::Buffer> vertices, indices;
    GL::Mesh mesh{NoCreate};
    std::tie(mesh, vertices, indices) = MeshTools::compile(Primitives::icosphereSolid(1), GL::BufferUsage::StaticDraw);

    const Matrix4 projection = Projection*Transformation*
        Matrix4::rotationZ(13.7_degf)*
        Matrix4::rotationX(-12.6_degf);

    Shaders::MeshVisualizer shader{Shaders::MeshVisualizer::Flag::Wireframe};
    shader.setColor(BaseColor)
        .setWireframeColor(OutlineColor)
        .setViewportSize(Vector2{ImageSize})
        .setTransformationProjectionMatrix(projection);

    mesh.draw(shader);

    return "meshvisualizer.png";
}

std::string ShaderVisualizer::flat() {
    std::unique_ptr<GL::Buffer> vertices, indices;
    GL::Mesh mesh{NoCreate};
    std::tie(mesh, vertices, indices) = MeshTools::compile(Primitives::uvSphereSolid(16, 32), GL::BufferUsage::StaticDraw);

    Shaders::Flat3D shader;
    shader.setColor(BaseColor)
        .setTransformationProjectionMatrix(Projection*Transformation);

    mesh.draw(shader);

    return "flat.png";
}

std::string ShaderVisualizer::vertexColor() {
    Trade::MeshData3D sphere = Primitives::uvSphereSolid(32, 64);

    /* Color vertices nearest to given position */
    auto target = Vector3{2.0f, 2.0f, 7.0f}.normalized();
    std::vector<Color3> colors;
    colors.reserve(sphere.positions(0).size());
    for(Vector3 position: sphere.positions(0))
        colors.push_back(Color3::fromHsv(Math::lerp(240.0_degf, 420.0_degf, Math::max(1.0f - (position - target).length(), 0.0f)), 0.75f, 0.75f));

    GL::Buffer vertices, indices;
    vertices.setData(MeshTools::interleave(sphere.positions(0), colors), GL::BufferUsage::StaticDraw);
    indices.setData(sphere.indices(), GL::BufferUsage::StaticDraw);

    GL::Mesh mesh;
    mesh.setPrimitive(GL::MeshPrimitive::Triangles)
        .setCount(sphere.indices().size())
        .addVertexBuffer(vertices, 0,
            Shaders::VertexColor3D::Position{},
            Shaders::VertexColor3D::Color{Shaders::VertexColor3D::Color::Components::Three})
        .setIndexBuffer(indices, 0, GL::MeshIndexType::UnsignedInt);

    Shaders::VertexColor3D shader;
    shader.setTransformationProjectionMatrix(Projection*Transformation);

    mesh.draw(shader);

    return "vertexcolor.png";
}

std::string ShaderVisualizer::vector() {
    Containers::Optional<Trade::ImageData2D> image;
    if(!_importer->openFile("vector.png") || !(image = _importer->image2D(0))) {
        Error() << "Cannot open vector.png";
        return "vector.png";
    }

    GL::Texture2D texture;
    texture.setMinificationFilter(GL::SamplerFilter::Linear)
        .setMagnificationFilter(GL::SamplerFilter::Linear)
        .setWrapping(GL::SamplerWrapping::ClampToEdge)
        .setStorage(1, GL::TextureFormat::RGBA8, image->size())
        .setSubImage(0, {}, *image);

    GL::Mesh mesh{NoCreate};
    std::unique_ptr<GL::Buffer> vertices;
    std::tie(mesh, vertices, std::ignore) = MeshTools::compile(Primitives::squareSolid(Primitives::SquareTextureCoords::Generate), GL::BufferUsage::StaticDraw);

    Shaders::Vector2D shader;
    shader.setColor(BaseColor)
        .bindVectorTexture(texture)
        .setTransformationProjectionMatrix({});

    GL::Renderer::enable(GL::Renderer::Feature::Blending);
    GL::Renderer::setBlendFunction(GL::Renderer::BlendFunction::One, GL::Renderer::BlendFunction::OneMinusSourceAlpha);
    GL::Renderer::setBlendEquation(GL::Renderer::BlendEquation::Add, GL::Renderer::BlendEquation::Add);

    mesh.draw(shader);

    GL::Renderer::disable(GL::Renderer::Feature::Blending);

    return "vector.png";
}

std::string ShaderVisualizer::distanceFieldVector() {
    Containers::Optional<Trade::ImageData2D> image;
    if(!_importer->openFile("vector-distancefield.png") || !(image = _importer->image2D(0))) {
        Error() << "Cannot open vector-distancefield.png";
        return "distancefieldvector.png";
    }

    GL::Texture2D texture;
    texture.setMinificationFilter(GL::SamplerFilter::Linear)
        .setMagnificationFilter(GL::SamplerFilter::Linear)
        .setWrapping(GL::SamplerWrapping::ClampToEdge)
        .setStorage(1, GL::TextureFormat::RGBA8, image->size())
        .setSubImage(0, {}, *image);

    GL::Mesh mesh{NoCreate};
    std::unique_ptr<GL::Buffer> vertices;
    std::tie(mesh, vertices, std::ignore) = MeshTools::compile(Primitives::squareSolid(Primitives::SquareTextureCoords::Generate), GL::BufferUsage::StaticDraw);

    Shaders::DistanceFieldVector2D shader;
    shader.setColor(BaseColor)
        .setOutlineColor(OutlineColor)
        .setOutlineRange(0.6f, 0.4f)
        .bindVectorTexture(texture)
        .setTransformationProjectionMatrix({});

    GL::Renderer::enable(GL::Renderer::Feature::Blending);
    GL::Renderer::setBlendFunction(GL::Renderer::BlendFunction::One, GL::Renderer::BlendFunction::OneMinusSourceAlpha);
    GL::Renderer::setBlendEquation(GL::Renderer::BlendEquation::Add, GL::Renderer::BlendEquation::Add);

    mesh.draw(shader);

    GL::Renderer::disable(GL::Renderer::Feature::Blending);

    return "distancefieldvector.png";
}

MAGNUM_WINDOWLESSAPPLICATION_MAIN(ShaderVisualizer)
