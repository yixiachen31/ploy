#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ===========================
// 虚函数表声明
// ===========================
typedef struct Shape Shape;
typedef struct ShapeVTable {
    float (*get_area)(Shape*);   // 虚函数1：计算面积
    void (*draw)(Shape*);        // 虚函数2：绘制图形
} ShapeVTable;

// ===========================
// 父类 Shape 定义
// ===========================
struct Shape {
    const ShapeVTable* vptr;     // 虚函数表指针
};

// ===========================
// 子类 Rectangle 定义
// ===========================
//子类拥有一个指向虚函数地址表 struct VTable 的指针 *vptr，
//虚函数地址表中存放了指向子类函数实现的指针，在实例化时已经设置好。
//因此 tr.calc_csm() 最终调用的是 BadTr::calc_csm()，
//这正是 C/C++ 实现多态的核心机制。

typedef struct {
    Shape base;      // 继承自 Shape，必须是第一个字段
    float width;
    float height;
} Rectangle;

// Rectangle 的 get_area 实现
float rectangle_get_area(Shape* shape) {
    Rectangle* rect = (Rectangle*)shape;
    return rect->width * rect->height;
}

// Rectangle 的 draw 实现
void rectangle_draw(Shape* shape) {
    Rectangle* rect = (Rectangle*)shape;
    printf("Rectangle: %.2f x %.2f\n", rect->width, rect->height);
}

// Rectangle 的虚函数表
const ShapeVTable rectangle_vtable = {
    rectangle_get_area,
    rectangle_draw
};

// Rectangle 的初始化函数，
//注册函数，注册rect->base.vptr虚函数表
//：把一段固定的函数（地址）组成的结构体（表）的头部地址给rect->base.vptr
void rectangle_init(Rectangle* rect, float width, float height) {
    rect->width = width;
    rect->height = height;
    rect->base.vptr = &rectangle_vtable;
}

// ===========================
// 子类 Circle 定义
// ===========================
typedef struct {
    Shape base;
    float radius;
} Circle;

// Circle 的 get_area 实现
float circle_get_area(Shape* shape) {
    Circle* c = (Circle*)shape;
    return M_PI * c->radius * c->radius;
}

// Circle 的 draw 实现
void circle_draw(Shape* shape) {
    Circle* c = (Circle*)shape;
    printf("Circle: radius = %.2f\n", c->radius);
}

// Circle 的虚函数表
const ShapeVTable circle_vtable = {
    circle_get_area,
    circle_draw
};

// Circle 的初始化函数
void circle_init(Circle* circle, float radius) {
    circle->radius = radius;
    circle->base.vptr = &circle_vtable;
}

// ===========================
// 多态调用函数
// ===========================
void print_area(Shape* shape) {
    float area = shape->vptr->get_area(shape);
    printf("Area: %.2f\n", area);
}

void draw_shape(Shape* shape) {
    shape->vptr->draw(shape);
}

// ===========================
// 主函数
// ===========================
int main() {
    Rectangle r;
    rectangle_init(&r, 3.0f, 4.0f);

    Circle c;
    circle_init(&c, 5.0f);

    // 使用基类指针调用多态函数
    Shape* shapes[2];
    shapes[0] = (Shape*)&r;
    shapes[1] = (Shape*)&c;

    for (int i = 0; i < 2; ++i) {
        draw_shape(shapes[i]);   // 多态调用 draw()
        print_area(shapes[i]);   // 多态调用 get_area()
        printf("\n");
    }

    return 0;
}

/*
还有一个问题，就是多级继承。
如果还有一个东西xxx，继承了rectangle，
理论上他也可以去调用最开始的基类中的虚函数地址表中的函数。
但是由于面向对象的封装性质，
按理来说那个xxx是只能看到他继承了rectangle，
而看不到更上面的。
那么对于xxx的多态，又该怎么办呢？
*/
