#ifndef ACTION_H
#define ACTION_H

class Action
{
    public:
        virtual void Evoke() = 0;
    private:
};

//-------------------------------------------

class Fight : public Action
{
    public:
        virtual void Evoke() override;
    private:
};

class Travel : public Action
{
    public:
        virtual void Evoke() override;
    private:
};

class Shop : public Action
{
    public:
        virtual void Evoke() override;
    private:
};

#endif ACTION_H