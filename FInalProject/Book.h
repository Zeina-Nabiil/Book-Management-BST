class Book
{
private:
    std::string title;
    std::string author;
    std::string category;
    int numOfPages;

public:
    // Parameterized constructor
    Book(std::string val1, std::string val2, std::string val3, int val4)
    {
        title = val1;
        author = val2;
        category = val3;
        numOfPages = val4;
    }
    // less than operator to compare books using their titles (operator overloading)
    bool operator<(const Book& obj2) const
    {
        return title < obj2.title;
    }
    // Equal to operator
    bool operator==(const Book& obj2) const
    {
        return title == obj2.title;
    }
    bool operator> (const Book& obj2) const
    {
        return title > obj2.title;
    }
    void printTitle()
    {
        std::cout<<"Book title : "<<title<<std::endl;
    }
    void print()
    {
        std::cout<<"Book title : "<<title<<std::endl;
        std::cout<<"Book author: "<<author<<std::endl;
        std::cout<<"Book category: "<<category<<std::endl;
        std::cout<<"Book number of pages: "<<numOfPages<<std::endl;
    }
    // Getter methods (read)
    std::string getTitle () const
    {
        return title;
    }
    std::string getAuthor () const
    {
        return author;
    }
    std::string getCategory () const
    {
        return category;
    }
    int getNumOfPages () const
    {
        return numOfPages;
    }
    // Setter methods (write)
    void setTitle (std::string value)
    {
        title = value;
    }
    void setAuthor (std::string value)
    {
        author = value;
    }
    void setCategory (std::string value)
    {
        category = value;
    }
    void setNumOfPages (int value)
    {
        numOfPages = value;
    }
};
