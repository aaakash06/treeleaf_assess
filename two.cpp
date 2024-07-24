#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

using namespace std; 

struct Vertex {
    int x, y, z;
};

class Box {
private:
    vector<Vertex> vertices;

public:
    Box(const vector<Vertex>& verts) : vertices(verts) {}

    vector<Vertex>& getVertices() {
        return vertices;
    }

    void setVertices(const vector<Vertex>& verts) {
        vertices = verts;
    }
};

class Transformation {
public:
    static shared_ptr<Box> rotateAboutX(std::shared_ptr<Box> box, double angle_x) {
        double rad = angle_x * M_PI / 180.0;
        double cosAngle = cos(rad);
        double sinAngle = sin(rad);

        vector<Vertex> newVertices;
        for (const auto& vertex : box->getVertices()) {
            int y_new = static_cast<int>(vertex.y * cosAngle - vertex.z * sinAngle);
            int z_new = static_cast<int>(vertex.y * sinAngle + vertex.z * cosAngle);
            newVertices.push_back({vertex.x, y_new, z_new});
        }

        box->setVertices(newVertices);
        return box;
    }

    static shared_ptr<Box> rotateAboutY(std::shared_ptr<Box> box, double angle_y) {
        double rad = angle_y * M_PI / 180.0;
        double cosAngle = cos(rad);
        double sinAngle = sin(rad);

        vector<Vertex> newVertices;
        for (const auto& vertex : box->getVertices()) {
            int x_new = static_cast<int>(vertex.x * cosAngle + vertex.z * sinAngle);
            int z_new = static_cast<int>(-vertex.x * sinAngle + vertex.z * cosAngle);
            newVertices.push_back({x_new, vertex.y, z_new});
        }

        box->setVertices(newVertices);
        return box;
    }

    static shared_ptr<Box> rotateAboutZ(std::shared_ptr<Box> box, double angle_z) {
        double rad = angle_z * M_PI / 180.0;
        double cosAngle = cos(rad);
        double sinAngle = sin(rad);

        vector<Vertex> newVertices;
        for (const auto& vertex : box->getVertices()) {
            int x_new = static_cast<int>(vertex.x * cosAngle - vertex.y * sinAngle);
            int y_new = static_cast<int>(vertex.x * sinAngle + vertex.y * cosAngle);
            newVertices.push_back({x_new, y_new, vertex.z});
        }

        box->setVertices(newVertices);
        return box;
    }

    static shared_ptr<Box> scale(std::shared_ptr<Box> box, double scale_factor) {
        vector<Vertex> newVertices;
        for (const auto& vertex : box->getVertices()) {
            int x_new = static_cast<int>(vertex.x * scale_factor);
            int y_new = static_cast<int>(vertex.y * scale_factor);
            int z_new = static_cast<int>(vertex.z * scale_factor);
            newVertices.push_back({x_new, y_new, z_new});
        }

        box->setVertices(newVertices);
        return box;
    }
};

int main() {
    vector<Vertex> vertices = {
        {0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0},
        {0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1}
    };

    shared_ptr<Box> box = make_shared<Box>(vertices);

cout<< "Give an angle" << endl; 
int angle; 
cin>> angle; 

cout<< "Give the scale factor" << endl; 
int scale; 
cin>> scale; 

    Transformation::rotateAboutX(box, angle);

    Transformation::rotateAboutY(box, angle);

    Transformation::rotateAboutZ(box, angle);

    Transformation::scale(box, scale);

    for (const auto& vertex : box->getVertices()) {
    cout << "Vertex: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")\n";
    }

    return 0;
}


