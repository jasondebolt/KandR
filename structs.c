#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

struct point {
        int x;
        int y;
};

typedef struct point Point;

struct rect {
        struct point p1;
        struct point p2;
};

struct rect RECT;

void printPoint(struct point p) {
        printf("point{x: %d, y: %d}\n", p.x, p.y);
}

void printRect(struct rect r) {
        printf("rect{point{%d, %d}, point{%d, %d}}\n", r.p1.x, r.p1.y, r.p2.x, r.p2.y);
}

void printInts(char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        int val;
        while((val = va_arg(args, int))) {
                printf("%d\t", val);
        }
        printf("\n");
        va_end(args);
}

struct point makePoint(int x, int y) {
        struct point p;
        p.x = x;
        p.y = y;
        return p;
}

double getDistance(struct point p1, struct point p2) {
        return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

struct point addPoints(struct point p1, struct point p2) {
        // remember, structs are passed by value just like everything else.
        p1.x += p2.x;
        p1.y += p2.y;
        return p1;
}

struct point getMiddlePoint(struct point p1, struct point p2) {
        struct point p3 = {(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
        return p3;
}

int pointInRect(struct point p, struct rect r) {
        return p.x >= r.p1.x && p.x < r.p2.x &&
                         p.y >= r.p1.y && p.y < r.p2.y;
}

void makeCanonicalRect(struct rect *rp) {
        int tmp;
        if (rp->p1.x > rp->p2.x) {
                tmp = rp->p1.x;
                rp->p1.x = rp->p2.x;
                rp->p2.x = tmp;
        }
        if (rp->p1.y > rp->p2.y) {
                tmp = rp->p1.y;
                rp->p1.y = rp->p2.y;
                rp->p2.y = tmp;
        }
}

void testPoint() {
        struct point x, y;
        x.x = 0, x.y = 0;
        y.x = 3, y.y = 4;
        assert(x.x == 0 && x.y == 0);
        assert(y.x == 3 && y.y == 4);
        Point z = {4, 4};
        assert(z.x == 4 && z.y == 4);
        printPoint(z);
        printf("point tested\n");
}

void testMakePoint() {
        struct point p = makePoint(3, 4);
        assert(p.x == 3 && p.y == 4);
        struct point p2 = {5, 6};
        assert(p2.x == 5 && p2.y == 6);
        printf("makePoint tested\n");
}

void testRect() {
        struct point p1 = {0, 0}, p2 = {3, 4};
        struct rect r;
        r.p1 = p1;
        r.p2 = p2;
        assert(r.p1.x == 0 && r.p1.y == 0);
        assert(r.p2.x == 3 && r.p2.y == 4);

        struct rect r2 = {{1, 2}, {3, 4}};
        assert(r2.p1.x == 1 && r2.p1.y == 2);
        assert(r2.p2.x == 3 && r2.p2.y == 4);

        struct rect r3;
        r3.p2.y = 9;
        // unitialized fields will be garbage.
        printRect(r3);
        // unitialized fields will be 0.
        assert(RECT.p1.x == 0 && RECT.p1.y == 0);
        assert(RECT.p2.x == 0 && RECT.p2.y == 0);
        printf("rect tested\n");
}

void testPointDistance() {
        struct point p1 = {0, 0};
        struct point p2 = {3, 4};
        assert(getDistance(p1, p2) == 5);
        assert(getDistance(p2, p1) == 5);
        printf("point distance tested\n");
}

void testPointAdd() {
        struct point p1 = {1, 2};
        struct point p2 = {3, 4};
        struct point p3 = addPoints(p1, p2);
        assert(p3.x == 4 && p3.y == 6);
        printf("point add tested\n");
}

void testGetMiddlePoint() {
        struct point p1 = {0, 0};
        struct point p2 = {4, 4};
        struct point p3 = getMiddlePoint(p1, p2);
        assert(p3.x == 2 && p3.y == 2);
        printf("getMiddlePoint tested.\n");
}

void testMakeCanonicalRect() {
        struct rect r1 = {{4, 4}, {0, 0}};
        struct rect *rp = &r1;
        makeCanonicalRect(rp);
        assert(r1.p1.x == 0 && r1.p1.y == 0);
        assert(r1.p2.x == 4 && r1.p2.y == 4);

        struct rect r2 = {{2, 0}, {0, 2}};
        rp = &r2;
        makeCanonicalRect(rp);
        assert(r2.p1.x == 0 && r2.p1.y == 0);
        assert(r2.p2.x == 2 && r2.p2.y == 2);
        printf("makeCanonicalRect tested.\n");
}

void testPointInRect() {
        struct rect r = {{0, 0}, {5, 5}};
        struct point p1 = {0, 0};
        struct point p2 = {1, 2};
        struct point p3 = {4, 5};
        struct point p4 = {5, 4};
        struct point p5 = {6, 9};
        assert(pointInRect(p1, r));
        assert(pointInRect(p2, r));
        assert(!pointInRect(p3, r) && !pointInRect(p4, r) && !pointInRect(p5, r));

        struct rect r2 = {{5, 5}, {0, 0}};
        assert(!pointInRect(p1, r2));
        assert(!pointInRect(p2, r2));

        printf("pointInRect tested.\n");
}

void testPrintInts() {
        printInts("", 6, 9);
}

int main() {
        testPrintInts();
        testPoint();
        testMakePoint();
        testRect();
        testPointDistance();
        testPointAdd();
        testGetMiddlePoint();
        testMakeCanonicalRect();
        testPointInRect();

        return 0;
}

