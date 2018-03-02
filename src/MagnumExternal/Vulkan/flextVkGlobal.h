#ifndef _flextVkGlobal_h_
#define _flextVkGlobal_h_
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

#include "MagnumExternal/Vulkan/flextGL.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DOXYGEN_GENERATING_OUTPUT /* So the macro names are preserved in the docs */

/* Per-instance function pointers */
extern FLEXTVK_EXPORT FlextVkInstance flextVkInstance;

/* VK_VERSION_1_0 */

#define vkCreateDevice flextVkInstance.CreateDevice
#define vkDestroyInstance flextVkInstance.DestroyInstance
#define vkEnumerateDeviceExtensionProperties flextVkInstance.EnumerateDeviceExtensionProperties
#define vkEnumerateDeviceLayerProperties flextVkInstance.EnumerateDeviceLayerProperties
#define vkEnumeratePhysicalDevices flextVkInstance.EnumeratePhysicalDevices
#define vkGetDeviceProcAddr flextVkInstance.GetDeviceProcAddr
#define vkGetPhysicalDeviceFeatures flextVkInstance.GetPhysicalDeviceFeatures
#define vkGetPhysicalDeviceFormatProperties flextVkInstance.GetPhysicalDeviceFormatProperties
#define vkGetPhysicalDeviceImageFormatProperties flextVkInstance.GetPhysicalDeviceImageFormatProperties
#define vkGetPhysicalDeviceMemoryProperties flextVkInstance.GetPhysicalDeviceMemoryProperties
#define vkGetPhysicalDeviceProperties flextVkInstance.GetPhysicalDeviceProperties
#define vkGetPhysicalDeviceQueueFamilyProperties flextVkInstance.GetPhysicalDeviceQueueFamilyProperties
#define vkGetPhysicalDeviceSparseImageFormatProperties flextVkInstance.GetPhysicalDeviceSparseImageFormatProperties

/* Per-device function pointers */
extern FLEXTVK_EXPORT FlextVkDevice flextVkDevice;

/* VK_VERSION_1_0 */

#define vkAllocateCommandBuffers flextVkDevice.AllocateCommandBuffers
#define vkAllocateDescriptorSets flextVkDevice.AllocateDescriptorSets
#define vkAllocateMemory flextVkDevice.AllocateMemory
#define vkBeginCommandBuffer flextVkDevice.BeginCommandBuffer
#define vkBindBufferMemory flextVkDevice.BindBufferMemory
#define vkBindImageMemory flextVkDevice.BindImageMemory
#define vkCmdBeginQuery flextVkDevice.CmdBeginQuery
#define vkCmdBeginRenderPass flextVkDevice.CmdBeginRenderPass
#define vkCmdBindDescriptorSets flextVkDevice.CmdBindDescriptorSets
#define vkCmdBindIndexBuffer flextVkDevice.CmdBindIndexBuffer
#define vkCmdBindPipeline flextVkDevice.CmdBindPipeline
#define vkCmdBindVertexBuffers flextVkDevice.CmdBindVertexBuffers
#define vkCmdBlitImage flextVkDevice.CmdBlitImage
#define vkCmdClearAttachments flextVkDevice.CmdClearAttachments
#define vkCmdClearColorImage flextVkDevice.CmdClearColorImage
#define vkCmdClearDepthStencilImage flextVkDevice.CmdClearDepthStencilImage
#define vkCmdCopyBuffer flextVkDevice.CmdCopyBuffer
#define vkCmdCopyBufferToImage flextVkDevice.CmdCopyBufferToImage
#define vkCmdCopyImage flextVkDevice.CmdCopyImage
#define vkCmdCopyImageToBuffer flextVkDevice.CmdCopyImageToBuffer
#define vkCmdCopyQueryPoolResults flextVkDevice.CmdCopyQueryPoolResults
#define vkCmdDispatch flextVkDevice.CmdDispatch
#define vkCmdDispatchIndirect flextVkDevice.CmdDispatchIndirect
#define vkCmdDraw flextVkDevice.CmdDraw
#define vkCmdDrawIndexed flextVkDevice.CmdDrawIndexed
#define vkCmdDrawIndexedIndirect flextVkDevice.CmdDrawIndexedIndirect
#define vkCmdDrawIndirect flextVkDevice.CmdDrawIndirect
#define vkCmdEndQuery flextVkDevice.CmdEndQuery
#define vkCmdEndRenderPass flextVkDevice.CmdEndRenderPass
#define vkCmdExecuteCommands flextVkDevice.CmdExecuteCommands
#define vkCmdFillBuffer flextVkDevice.CmdFillBuffer
#define vkCmdNextSubpass flextVkDevice.CmdNextSubpass
#define vkCmdPipelineBarrier flextVkDevice.CmdPipelineBarrier
#define vkCmdPushConstants flextVkDevice.CmdPushConstants
#define vkCmdResetEvent flextVkDevice.CmdResetEvent
#define vkCmdResetQueryPool flextVkDevice.CmdResetQueryPool
#define vkCmdResolveImage flextVkDevice.CmdResolveImage
#define vkCmdSetBlendConstants flextVkDevice.CmdSetBlendConstants
#define vkCmdSetDepthBias flextVkDevice.CmdSetDepthBias
#define vkCmdSetDepthBounds flextVkDevice.CmdSetDepthBounds
#define vkCmdSetEvent flextVkDevice.CmdSetEvent
#define vkCmdSetLineWidth flextVkDevice.CmdSetLineWidth
#define vkCmdSetScissor flextVkDevice.CmdSetScissor
#define vkCmdSetStencilCompareMask flextVkDevice.CmdSetStencilCompareMask
#define vkCmdSetStencilReference flextVkDevice.CmdSetStencilReference
#define vkCmdSetStencilWriteMask flextVkDevice.CmdSetStencilWriteMask
#define vkCmdSetViewport flextVkDevice.CmdSetViewport
#define vkCmdUpdateBuffer flextVkDevice.CmdUpdateBuffer
#define vkCmdWaitEvents flextVkDevice.CmdWaitEvents
#define vkCmdWriteTimestamp flextVkDevice.CmdWriteTimestamp
#define vkCreateBuffer flextVkDevice.CreateBuffer
#define vkCreateBufferView flextVkDevice.CreateBufferView
#define vkCreateCommandPool flextVkDevice.CreateCommandPool
#define vkCreateComputePipelines flextVkDevice.CreateComputePipelines
#define vkCreateDescriptorPool flextVkDevice.CreateDescriptorPool
#define vkCreateDescriptorSetLayout flextVkDevice.CreateDescriptorSetLayout
#define vkCreateEvent flextVkDevice.CreateEvent
#define vkCreateFence flextVkDevice.CreateFence
#define vkCreateFramebuffer flextVkDevice.CreateFramebuffer
#define vkCreateGraphicsPipelines flextVkDevice.CreateGraphicsPipelines
#define vkCreateImage flextVkDevice.CreateImage
#define vkCreateImageView flextVkDevice.CreateImageView
#define vkCreatePipelineCache flextVkDevice.CreatePipelineCache
#define vkCreatePipelineLayout flextVkDevice.CreatePipelineLayout
#define vkCreateQueryPool flextVkDevice.CreateQueryPool
#define vkCreateRenderPass flextVkDevice.CreateRenderPass
#define vkCreateSampler flextVkDevice.CreateSampler
#define vkCreateSemaphore flextVkDevice.CreateSemaphore
#define vkCreateShaderModule flextVkDevice.CreateShaderModule
#define vkDestroyBuffer flextVkDevice.DestroyBuffer
#define vkDestroyBufferView flextVkDevice.DestroyBufferView
#define vkDestroyCommandPool flextVkDevice.DestroyCommandPool
#define vkDestroyDescriptorPool flextVkDevice.DestroyDescriptorPool
#define vkDestroyDescriptorSetLayout flextVkDevice.DestroyDescriptorSetLayout
#define vkDestroyDevice flextVkDevice.DestroyDevice
#define vkDestroyEvent flextVkDevice.DestroyEvent
#define vkDestroyFence flextVkDevice.DestroyFence
#define vkDestroyFramebuffer flextVkDevice.DestroyFramebuffer
#define vkDestroyImage flextVkDevice.DestroyImage
#define vkDestroyImageView flextVkDevice.DestroyImageView
#define vkDestroyPipeline flextVkDevice.DestroyPipeline
#define vkDestroyPipelineCache flextVkDevice.DestroyPipelineCache
#define vkDestroyPipelineLayout flextVkDevice.DestroyPipelineLayout
#define vkDestroyQueryPool flextVkDevice.DestroyQueryPool
#define vkDestroyRenderPass flextVkDevice.DestroyRenderPass
#define vkDestroySampler flextVkDevice.DestroySampler
#define vkDestroySemaphore flextVkDevice.DestroySemaphore
#define vkDestroyShaderModule flextVkDevice.DestroyShaderModule
#define vkDeviceWaitIdle flextVkDevice.DeviceWaitIdle
#define vkEndCommandBuffer flextVkDevice.EndCommandBuffer
#define vkFlushMappedMemoryRanges flextVkDevice.FlushMappedMemoryRanges
#define vkFreeCommandBuffers flextVkDevice.FreeCommandBuffers
#define vkFreeDescriptorSets flextVkDevice.FreeDescriptorSets
#define vkFreeMemory flextVkDevice.FreeMemory
#define vkGetBufferMemoryRequirements flextVkDevice.GetBufferMemoryRequirements
#define vkGetDeviceMemoryCommitment flextVkDevice.GetDeviceMemoryCommitment
#define vkGetDeviceQueue flextVkDevice.GetDeviceQueue
#define vkGetEventStatus flextVkDevice.GetEventStatus
#define vkGetFenceStatus flextVkDevice.GetFenceStatus
#define vkGetImageMemoryRequirements flextVkDevice.GetImageMemoryRequirements
#define vkGetImageSparseMemoryRequirements flextVkDevice.GetImageSparseMemoryRequirements
#define vkGetImageSubresourceLayout flextVkDevice.GetImageSubresourceLayout
#define vkGetPipelineCacheData flextVkDevice.GetPipelineCacheData
#define vkGetQueryPoolResults flextVkDevice.GetQueryPoolResults
#define vkGetRenderAreaGranularity flextVkDevice.GetRenderAreaGranularity
#define vkInvalidateMappedMemoryRanges flextVkDevice.InvalidateMappedMemoryRanges
#define vkMapMemory flextVkDevice.MapMemory
#define vkMergePipelineCaches flextVkDevice.MergePipelineCaches
#define vkQueueBindSparse flextVkDevice.QueueBindSparse
#define vkQueueSubmit flextVkDevice.QueueSubmit
#define vkQueueWaitIdle flextVkDevice.QueueWaitIdle
#define vkResetCommandBuffer flextVkDevice.ResetCommandBuffer
#define vkResetCommandPool flextVkDevice.ResetCommandPool
#define vkResetDescriptorPool flextVkDevice.ResetDescriptorPool
#define vkResetEvent flextVkDevice.ResetEvent
#define vkResetFences flextVkDevice.ResetFences
#define vkSetEvent flextVkDevice.SetEvent
#define vkUnmapMemory flextVkDevice.UnmapMemory
#define vkUpdateDescriptorSets flextVkDevice.UpdateDescriptorSets
#define vkWaitForFences flextVkDevice.WaitForFences

#endif

#ifdef __cplusplus
}
#endif

#endif
