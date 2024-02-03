//==============================================================================
// in-out-rect-trian.c - содержит обработчики специализаций ввода-вывода
// параметров для прямоугольника и треугольника как фигуры
//==============================================================================

#include <stdio.h>
#include "shape.h"

//------------------------------------------------------------------------------
// Обработчик специализации ввода прямоугольника
void InShape<struct shape<struct rectangle> *s>(FILE* ofst) {
  struct rectangle rec = s->@;
  rectangle* r = &rec;
  InRectangle(r);
}

//------------------------------------------------------------------------------
// Обработчик специализации вывода прямоугольника
void OutShape<struct shape<struct rectangle> *s>(FILE* ofst) {
  struct rectangle rec = s->@;
  rectangle* r = &rec;
  OutRectangle(r);
}

//------------------------------------------------------------------------------
// Обработчик специализации ввода треугольника
void InShape<struct shape<struct triangle> *s>(FILE* ofst) {
  struct triangle tri = s->@;
  InTriangle(&tri);
}

//------------------------------------------------------------------------------
// Обработчик специализации вывода треугольника
void OutShape<struct shape<struct triangle> *s>(FILE* ofst) {
  struct triangle tri = s->@;
  OutTriangle(&tri);
}
