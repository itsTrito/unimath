#ifndef LIFE_CYCLE_OBJECT_HPP
#define LIFE_CYCLE_OBJECT_HPP

namespace GEngine
{
  class LifeCycleObject
  {
  public:
    virtual void Init() = 0;
    virtual void Start() = 0;
    virtual void Update(double deltaTime) = 0;
    virtual void LateUpdate(double deltaTime) = 0;
    virtual void Quit() = 0;
    virtual void Destroy() = 0;
  };
} // namespace GEngine

#endif