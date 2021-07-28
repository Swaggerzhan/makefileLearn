class A;
class B;


class Bind{
public:

    Bind(A* a, B* b);
    ~Bind();
    void show();

private:

    A* a_;
    B* b_;

};