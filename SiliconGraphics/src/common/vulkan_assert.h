#include <stdexcept>
#include <vulkan/vulkan.h>

namespace Silicon {

inline void VkAssert(VkResult result, const char* msg) {
	if (result != VK_SUCCESS) {
		throw std::runtime_error(msg);
	}
}

}
