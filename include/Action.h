#pragma once

// class Action 
// {
// public:
//     virtual void Executez() = 0;
// };

template <typename T = void>
class Action 
{
public:
    virtual void Executez(T) = 0;
};

template <>
class Action<void> 
{
public:
    virtual void Executez() = 0;
};
