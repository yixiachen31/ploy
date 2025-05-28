#include <iostream>
#include <cmath>    // 为了使用 M_PI

// ===============================
// 抽象基类 Shape
// ===============================
class Shape {
public:
    // 虚函数：求面积
    virtual float get_area() const = 0;

    // 虚函数：绘制图形
    virtual void draw() const = 0;

    // 虚析构函数：确保删除派生类对象时正确析构
    virtual ~Shape() {}
};

// ===============================
// Rectangle 类，继承自 Shape
// ===============================
class Rectangle : public Shape {
private:
    float width;
    float height;

public:
    // 构造函数
    Rectangle(float w, float h) : width(w), height(h) {}

    // 重写虚函数
    float get_area() const override {
        return width * height;
    }

    void draw() const override {
        std::cout << "Rectangle: " << width << " x " << height << std::endl;
    }
};

// ===============================
// Circle 类，继承自 Shape
// ===============================
class Circle : public Shape {
private:
    float radius;

public:
    Circle(float r) : radius(r) {}

    float get_area() const override {
        return M_PI * radius * radius;
    }

    void draw() const override {
        std::cout << "Circle: radius = " << radius << std::endl;
    }
};

// ===============================
// 多态调用函数
// ===============================
void print_area(const Shape* shape) {
    std::cout << "Area: " << shape->get_area() << std::endl;
}

void draw_shape(const Shape* shape) {
    shape->draw();
}

// ===============================
// 主函数
// ===============================
int main() {
    // 创建两个派生类对象
    Rectangle r(3.0f, 4.0f);
    Circle c(5.0f);

    // 使用基类指针调用多态方法
    Shape* shapes[2] = { &r, &c };

    for (int i = 0; i < 2; ++i) {
        draw_shape(shapes[i]);   // 多态调用
        print_area(shapes[i]);   // 多态调用
        std::cout << std::endl;
    }

    return 0;
}
