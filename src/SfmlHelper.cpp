#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

// Vector Helper

float vectorLength(sf::Vector2f v) {
    return std::sqrt(v.x*v.x+v.y*v.y);
}

sf::Vector2f normalizeToLength(sf::Vector2f v, float length) {
    sf::Vector2f result(v);
    float vLength = vectorLength(result);

    result.x = (result.x / vLength) * length;
    result.y = (result.y / vLength) * length;
    
    return result;
}

sf::Vector3f crossProduct(sf::Vector3f a, sf::Vector3f b) {
    sf::Vector3f result;

    result.x = a.y*b.z-a.z*b.y;
    result.y = a.z*b.x-a.x*b.z;
    result.z = a.x*b.y-a.y*b.x;

    return result;
}

sf::Vector2f moveTowards(sf::Vector2f from, sf::Vector2f to, float distance) {
    sf::Vector2f step = to - from;
    step /= vectorLength(step);
    step *= distance;
    return from + step;
}

// OpenGL Draw Helper

void drawTriangle(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector3f color) {
    glBegin(GL_TRIANGLES);
        glColor3f(color.x, color.y, color.z);

        glVertex3f(a.x, a.y, 0.0f);
        glVertex3f(b.x, b.y, 0.0f);
        glVertex3f(c.x, c.y, 0.0f);
    glEnd();
}

void drawCircle(sf::Vector2f center, float radius, int segments, sf::Vector3f color) {
    float radiant = M_PI / segments;

    for (int angle = 0; angle < 360; ++angle) {
        drawTriangle(
            center, 
            sf::Vector2f(center.x + radius * cos(radiant * angle), center.y + radius * sin(radiant * angle)),
            sf::Vector2f(center.x + radius * cos(radiant * (angle + 1)), center.y + radius * sin(radiant * (angle + 1))),
            color);
    }
}

void drawLine(sf::Vector2f from, sf::Vector2f to, sf::Vector3f color) {
    glBegin(GL_LINES);
        glColor3f(color.x, color.y, color.z);

        glVertex3f(from.x, from.y, 0.0f);
        glVertex3f(to.x, to.y, 0.0f);
    glEnd();
}

void drawPoint(sf::Vector2f v, sf::Vector3f color) {
    glBegin(GL_LINES);
        glColor3f(color.x, color.y, color.z);

        glVertex3f((v.x) + 0.1, v.y, 0.0f);
        glVertex3f((v.x) - 0.1, v.y, 0.0f);
        glVertex3f(v.x, (v.y) + 0.1, 0.0f);
        glVertex3f(v.x, (v.y) - 0.1, 0.0f);
    glEnd();
}

sf::Vector3f getColor(float x) {
    if (x < 0 || x > 1) {
        return sf::Vector3f(0.0f, 0.0f, 0.0f);
    }

    float red = 0.0f;
    if ((x >= 0.0f && x <= 1.0f/6.0f) || (x >= 5.0f/6.0f && x <= 1.0f)) {
        red = 1.0f;
    }
    else if (x > 1.0f/6.0f && x <= 2.0f/6.0f) {
        red = -((x - 1.0f/6.0f) * 6) + 1;
    }
    else if (x >= 4.0f/6.0f && x < 1) {
        red = (x - 4.0f/6.0f) * 6;
    }

    float green = 0.0f;
    if (x >= 0 && x < 1.0f/6.0f) {
        green = x * 6;
    }
    else if (x >= 1.0f/6.0f && x <= 3.0f/6.0f) {
        green = 1.0f;
    }
    else if (x > 3.0f/6.0f && x <= 4.0f/6.0f) {
        green = -((x - 3.0f/6.0f) * 6) + 1;
    }

    float blue = 0.0f;
    if (x >= 2.0f/6.0f && x < 3.0f/6.0f) {
        blue = (x - 2.0f/6.0f) * 6;
    }
    else if (x >= 3.0f/6.0f && x <= 5.0f/6.0f) {
        blue = 1.0f;
    }
    else if (x > 5.0f/6.0f && x <= 1.0f) {
        blue = -((x - 5.0f/6.0f) * 6) + 1;
    }

    return sf::Vector3f(red, green, blue);
}
