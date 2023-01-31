#define RTCSDK_COM_NO_LEAK_DETECTION

#include <iostream>
#include <rtcsdk/interfaces.h>
#include <windows.h>

// Declare sample interface
RTCSDK_DEFINE_INTERFACE(ISampleInterface, "{AB9A7AF1-6792-4D0A-83BE-8252A8432B45}")
{
  [[nodiscard]] virtual int sum(int a, int b) const noexcept = 0;
  [[nodiscard]] virtual int get_answer() const noexcept = 0;
};

// Define implementation
class __declspec(novtable) sample_object : public rtcsdk::object<sample_object, ISampleInterface>
{
public:
  explicit sample_object(int default_answer) noexcept : default_answer_{default_answer}
  {
  }

private:
  // ISampleInterface implementation
  [[nodiscard]] int sum(int a, int b) const noexcept override
  {
    return a + b;
  }

  [[nodiscard]] int get_answer() const noexcept override
  {
    return default_answer_;
  }

  int default_answer_;
};

int main()
{
  // Create new instance and get its ISampleInterface interface pointer
  {
    auto obj = sample_object::create_instance(42).to_ptr();
    std::cout << obj->sum(obj->get_answer(), 5);
  }
}
