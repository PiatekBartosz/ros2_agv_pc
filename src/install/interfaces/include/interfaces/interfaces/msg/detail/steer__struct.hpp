// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from interfaces:msg/Steer.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__STEER__STRUCT_HPP_
#define INTERFACES__MSG__DETAIL__STEER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__interfaces__msg__Steer __attribute__((deprecated))
#else
# define DEPRECATED__interfaces__msg__Steer __declspec(deprecated)
#endif

namespace interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Steer_
{
  using Type = Steer_<ContainerAllocator>;

  explicit Steer_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit Steer_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _data_type =
    std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>>;
  _data_type data;

  // setters for named parameter idiom
  Type & set__data(
    const std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    interfaces::msg::Steer_<ContainerAllocator> *;
  using ConstRawPtr =
    const interfaces::msg::Steer_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<interfaces::msg::Steer_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<interfaces::msg::Steer_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::Steer_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::Steer_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::Steer_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::Steer_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<interfaces::msg::Steer_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<interfaces::msg::Steer_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__interfaces__msg__Steer
    std::shared_ptr<interfaces::msg::Steer_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__interfaces__msg__Steer
    std::shared_ptr<interfaces::msg::Steer_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Steer_ & other) const
  {
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const Steer_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Steer_

// alias to use template instance with default allocator
using Steer =
  interfaces::msg::Steer_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__STEER__STRUCT_HPP_
