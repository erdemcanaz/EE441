class Date{
    private:
        int day;
        int month;
        int year;
    public:
        Date(int d=1, int m=1, int y=1900);
        void printDate(void) const;
        int jumpYear(int j);
        void setDate(int d, int m, int y);
};