class Student: public Person {  // public inheritance
public:
    Student(const std::string &name, const std::string &studentID); // init name and ID
    ~Student();                   // destructor
    std::string getInfo() const;  // Person::getInfo() - get name and studentID
private:
    std::string studentID;        // the student ID of the student
};
