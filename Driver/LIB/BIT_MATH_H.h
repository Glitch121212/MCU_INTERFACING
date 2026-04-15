#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(var,BIT) (var |= (1<<BIT))
#define CLR_BIT(var, BIT) (var&=(~(1<<BIT)))
#define TOGGLE_BIT(var,BIT) (Var^=(1<<BIT))
#define GET_BIT(VAR,BIT)   ((VAR>>BIT)&1)

#endif