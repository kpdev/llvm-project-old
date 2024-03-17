
// RUN: %clang -c %S/Inputs/Figure.c -o %S/f.o
// RUN: %clang -c %S/Inputs/Triangle.c -o %S/t.o
// RUN: %clang -c %s -o %S/a.o
// RUN: %clang %S/f.o %S/t.o %S/a.o -o %S/a.out
// RUN: %S/a.out | FileCheck %s -check-prefix=CHECK-RT
// RUN: rm %S/a.out %S/f.o %S/t.o %S/a.o

#include "Inputs/pp-linked-figure.h"
#include "Inputs/pp-linked-triangle.h"
#include <stdio.h>

typedef struct Rhombus { int a, b; } Rhombus;
// Check version without struct key word
Figure + < Rhombus; >;

void PrintFigure<Figure<Rhombus> *p>() {
    struct Figure<Rhombus> r = *p;
    printf(">>> Rhombus: color = %d, a = %d, b = %d\n",
            r.color, r.@a, r.@b);
}

void PrintFigureWithArg<struct Figure* f>(int i)
{
    printf(">>> PrintFigureWithArg Default Color = %d, Param = %d\n",
        f->color,
        i);
}

void PrintFigureWithArg<struct Figure<struct Rhombus> *p>(int i)
{
    struct Figure<struct Rhombus> r = *p;
    printf(">>> PrintFigureWithArg Rhombus Color = %d, \
            a = %d, b = %d, Param = %d\n",
        r.color,
        r.@a,
        r.@b,
        i);
}


struct Simple {} < >;

struct Decorator {
} < struct Simple; >;

struct Simple + < struct Decorator;> ;
struct Simple + < struct Circle;> ;

int main()
{
    struct Simple< Decorator < Simple < Circle > > > sd;

    // CHECK-RT: FigCircle: 42 4294967295
    // CHECK-RT-NEXT: Circle tags check: [1]
    printCircle();
    // CHECK-RT-NEXT: FigRect: 5 7 255
    // CHECK-RT-NEXT: Rectangle tags check: [1]
    printRectangle();
    // CHECK-RT-NEXT: FigTriangle: 1 2 3 1
    // CHECK-RT-NEXT: Triangle tags check: [1]
    printTriangle();

    // CHECK-RT: Figure tags: 4
    // CHECK-RT: Circle tag: 1
    // CHECK-RT: Rectangle tag: 2
    // CHECK-RT: Triangle tag: 3
    // CHECK-RT: Rhombus tag: 4
    printf("Figure tags: %d\n", __pp_tags_Figure);
    printf("Circle tag: %d\n", __pp_tag___pp_struct_Figure__Circle);
    printf("Rectangle tag: %d\n", __pp_tag___pp_struct_Figure__Rectangle);
    printf("Triangle tag: %d\n", __pp_tag___pp_struct_Figure__Triangle);
    printf("Rhombus tag: %d\n", __pp_tag___pp_struct_Figure__Rhombus);

    struct Figure<struct Circle> fc;
    fc.color = 111;
    fc.@r = 100;

    // CHECK-RT: PrintFigure Default body
    PrintFigure<&fc>();

    // CHECK-RT: >>> Triangle: color = 555, a = 10, b = 20, c = 30
    struct Figure<struct Triangle> ft;
    ft.color = 555;
    ft.@a = 10;
    ft.@b = 20;
    ft.@c = 30;
    PrintFigure<&ft>();


    // CHECK-RT: >>> Rectangle: color = 333, w = 22, h = 11
    struct Figure<struct Rectangle> fr;
    fr.color = 333;
    fr.@w = 22;
    fr.@h = 11;
    PrintFigure<&fr>();

    // CHECK-RT: >>> Rhombus: color = 999, a = 10000, b = 20000
    struct Figure<struct Rhombus> frh;
    frh.color = 999;
    frh.@a = 10000;
    frh.@b = 20000;
    PrintFigure<&frh>();

    // CHECK-RT: >>> PrintFigureWithArg Default Color = 333, Param = 111
    PrintFigureWithArg<&fr>(111);

    // CHECK-RT: >>> PrintFigureWithArg Rhombus Color = 999, a = 10000, b = 20000, Param = 42
    PrintFigureWithArg<&frh>(42);

    // CHECK-RT: >>> PrintFigureWithArg Rhombus
    struct Figure* Ptr = create_spec<struct Figure<struct Rhombus> >();
    PrintFigureWithArg<Ptr>(42);

    // Test access to tail part
    struct Figure<struct Circle> f_test;
    struct Circle cc1 = f_test.@;
    f_test.@ = cc1;
    struct Circle* ptr_cc1 = &(f_test.@);
    ptr_cc1->r = 66;

    struct Figure<struct Circle>* f_ptr = &f_test;
    struct Circle cc2 = f_ptr->@;
    struct Circle* ptr_cc2 = &(f_ptr->@);
    ptr_cc2->r = 55;

    return 0;
}
