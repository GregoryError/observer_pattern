#include <iostream>
#include <string>
#include <vector>

class Subject
{
private:
    std::string data;
    std::vector<class Observer*> v_observers;
public:
    void addObserver(Observer* obs) {
        v_observers.push_back(obs);
    }
    void setData(const std::string& s) {
        data = s;
        notify();
    }
    std::string getData() {
        return data;
    }
    void notify();
};

class Observer
{
    Subject* model;
public:
    Observer(Subject* sub) {
        model = sub;
        model->addObserver(this);
    }
    virtual void update() = 0;
    virtual ~Observer() {}
protected:
    Subject* getSubject() {
        return model;
    }
};

void Subject::notify() {
    for (const auto o : v_observers)
        o->update();
}

class DirectShowWidget : public Observer
{
public:
    DirectShowWidget(Subject* s) :
        Observer(s) {}
    void update() override {
        std::cout << "Direct show widget: "
                  << getSubject()->getData()
                  << "\n";
    }
};

class ReverseShowWidget : public Observer
{
public:
    ReverseShowWidget(Subject* s) :
        Observer(s) {}
    void update() override {
        std::string t_str;
        size_t i = getSubject()->getData().size();
        for (; i != -1; --i)
            t_str += getSubject()->getData()[i];

        std::cout << "Reverse show widget: "
                  << t_str << "\n";
    }
};

int main(int argc, char* argv[])
{
    Subject subj;
    DirectShowWidget directWidget(&subj);
    ReverseShowWidget revWidget(&subj);

    std::string user_input;

    while (user_input != "quit")
    {
        std::cout << "Your data (quit for exit):\n";
        std::cin >> user_input;
        std::cout << '\n';
        subj.setData(user_input);
        std::cout << '\n';
    }

    return EXIT_SUCCESS;
}
























































