#include "../headers/triangle.h"

TRIANGLE::TRIANGLE(VECTOR3 v1, VECTOR3 v2, VECTOR3 v3, VECTOR3 norm, COLOR col)
{
    vertex[0] = v1;
    vertex[1] = v2;
    vertex[2] = v3;

    if(norm.isNull())
        computeNormal();
    else
        normal = norm;

    color = col;
}

void TRIANGLE::computeNormal()
{
    VECTOR3 v3v1(vertex[2]-vertex[0]);
    VECTOR3 v2v1(vertex[1]-vertex[0]);
    normal = v2v1.cross(v3v1);
    normal.normalize();
}

bool TRIANGLE::intersect(POINT origin, VECTOR3 direction, double &depth) const
{
    //algorithm used:  http://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
    //QVector3D d = direction;
    VECTOR3 e1 = vertex[1] - vertex[0];
    VECTOR3 e2 = vertex[2] - vertex[0];
    VECTOR3 p = direction.cross(e2);// QVector3D::crossProduct(d, e2);
    float det = e1.dot(p);// QVector3D::dotProduct(e1, p);
    if(det > -EPSILON && det < EPSILON)
        return false;
    float inv_det = 1.f / det;

    VECTOR3 t = VECTOR3(origin) - vertex[0];

    float u = (t.dot(p) * inv_det); // QVector3D::dotProduct(t, p) * inv_det);
    if(u < 0.f || u > 1.f)
        return false;

    //QVector3D q = QVector3D::crossProduct(t, e1);
    VECTOR3 q = t.cross(e1);

    float v = direction.dot(q) * inv_det; // (QVector3D::dotProduct(d, q) * inv_det);
    if(v < 0.f || (u + v) > 1.f)
        return false;

    float dist = e2.dot(q) * inv_det; // QVector3D::dotProduct(e2, q) * inv_det;
    if(dist > EPSILON)
    {
        //DEBUG PRINT
        //std::cout << "getRayIntersection - Treffer: " << dist << std::endl;
        depth = dist;
        return true;
    }

    return false;
}

