#include "Book.h"

// Create a class that represents the node
class BSTNode
{
public:
    //BSTNode consists of (1) a book object, (2) a left pointer, and (3) a right pointer.
    Book obj;
    BSTNode* Left;
    BSTNode* Right;

    //default constructor
    BSTNode() : obj("","","",0),Left(nullptr),Right(nullptr) // Initializer list
    {
         // title , author and category are initialized as empty strings , No. of pages initialized to zero
         // Left and Right pointers initialized to NULL
    }
    // parameterized constructor
    BSTNode(const Book& book) : obj(book),Left(nullptr),Right(nullptr)
    {

    }
};

// Create a class for BST
class BST
{
public:
    // Root is a pointer that  points to the first node in the tree
    BSTNode* Root;

    // default constructor
    BST()
    {
        Root = nullptr;
    }
    // Insert Method for user input
    void BSTInsert(const Book& newBook)
    {
        Root = BSTInsert(Root,newBook);
    }
    // Remove Method for user
    bool Remove(const std::string& title)
    {
         bool removed = false;
         Root = Remove(Root,title,removed);
         if(removed)
         {
             std::cout<<"Book removed."<<std::endl;
         }
         else
         {
             std::cout<<"Book not found."<<std::endl;
         }
         return removed ;
    }
    // Search method for user by title
    bool SearchTitle(const std::string& title)
    {
        BSTNode* result = SearchTitle(Root,title);
        if(result == nullptr) // Title not found
        {
            std::cout<<"Book not found."<<std::endl;
            return false;
        }
        else
        {
            std::cout<<"Book found."<<std::endl;
            result->obj.print();
            return true;
        }
    }
    // Search method for user by author
    bool SearchAuthor(const std::string& author)
    {
      bool flag = false;
      SearchAuthor(Root,author,flag);
      if(!flag)
      {
          std::cout<<"Author not found."<<std::endl;
          return false;
      }
      else
      {
          std::cout<<"Books written by author : "<<author<<std::endl;
          return true;
      }
    }
    // Search method for user by category
    bool SearchCategory(const std::string& category)
    {
      bool flag = false;
      SearchCategory(Root,category,flag);
      if(!flag)
      {
          std::cout<<"Category not found."<<std::endl;
          return false;
      }
      else
      {
          std::cout<<"Books in Category : "<<category<<std::endl;
          return true;
      }
    }
    // Display in an ascending order.
    void DisplayAscending ()
    {
        if(Root == nullptr)
        {
            std::cout << "No books to display." << std::endl;
            return;
        }
        std::cout << "Books in ascending order:" << std::endl;
        TraverseAsc(Root);
    }
    // Display in a descending order.
    void DisplayDescending ()
    {
        if(Root == nullptr)
        {
            std::cout << "No books to display." << std::endl;
            return;
        }
        std::cout << "Books in descending order:" << std::endl;
        TraverseDesc(Root);
    }
    // Destructor
    ~BST()
    {
        Clear(Root); // Clean up all nodes starting from the root
        std::cout<<"Dynamic memory deallocation done."<<std::endl;
    }

private:
    // Insert operation to add data of books
    // Insert method returns a pointer that points to the place where it stopped
    BSTNode* BSTInsert (BSTNode* node , Book newBook)  // node is a pointer that points to the root of the tree
    {
        if(node == nullptr) // tree is empty
        {
            node = new BSTNode(newBook);
            return node;
        }
        if(newBook < node->obj) // tree is not empty
        {
            node->Left= BSTInsert(node->Left , newBook); // Recursion
        }
        else
        {
            node->Right= BSTInsert(node->Right , newBook); // Recursion
        }
        return node;
    }
    // Method to find maximum
    BSTNode* FindMax(BSTNode* node)
    {
        if(node == nullptr)
            return nullptr;
        else if (node->Right == nullptr)
            return node;
        else
            return FindMax(node->Right);
    }
    // Deletion/Removal Method by title
    BSTNode* Remove (BSTNode* node , const std::string& title,bool& removed)
    {
        if(node == nullptr) // No items in the tree , therefore no items to be deleted
            return nullptr;
        if(title < node->obj.getTitle()) // item exists in the left subtree
            node->Left = Remove(node->Left ,title,removed);  // recursion
        else if (title > node->obj.getTitle()) // item exists in the right subtree
            node->Right = Remove(node->Right ,title,removed);
        else
            {
                removed = true;
                // case (1): node that needs to be deleted is a leaf node
                if(node->Left == nullptr && node->Right == nullptr)
                {
                    delete node;
                    return nullptr;
                }
                // case (2): node that needs to be deleted has one child
                else if(node->Left != nullptr && node->Right == nullptr) // one child on the left
                {
                    BSTNode* temp = node->Left;
                    delete node;
                    return temp; // Return the left child to parent
                }
                else if(node->Left == nullptr && node->Right != nullptr) // one child on the right
                {
                    BSTNode* temp = node->Right;
                    delete node;
                    return temp; // Return the right child to parent
                }
                // case (3): node that needs to be deleted has two children
                else
                {
                    // Find the maximum node in the left subtree
                    BSTNode* Maximum = FindMax(node->Left);

                    // Replace current node's value with the maximum node's value
                    node->obj = Maximum->obj;

                    // Recursively delete the maximum node
                    node->Left = Remove(node->Left,Maximum->obj.getTitle(),removed);
                }
            }
            return node;
    }
    // Search Method for searching by title
    BSTNode* SearchTitle(BSTNode* node ,const std::string& title)
    {
        if(node == nullptr) // Tree is empty or title not found
        {
            return nullptr;
        }
        else if(node->obj.getTitle() == title) // Title matches the current node
        {
            return node;
        }
        else if(title < node->obj.getTitle()) // Search in the left subtree
        {
            return SearchTitle(node->Left,title);
        }
        else // Search in the right subtree
        {
            return SearchTitle(node->Right,title);
        }
    }
    // Search Method for searching by author
    void SearchAuthor(BSTNode* node ,const std::string& author, bool& flag)
    {
        if(node == nullptr) // no items to search for
            return ;

        SearchAuthor(node->Left,author,flag);

        // Check if the current node matches the author
        if(node->obj.getAuthor() == author)
        {
            node->obj.print();
            flag = true;
        }

        SearchAuthor(node->Right,author,flag);

    }
    // Search Method for searching by category
    void SearchCategory(BSTNode* node ,const std::string& category, bool& flag)
    {
        if(node == nullptr) // no items to search for
            return ;

        SearchCategory(node->Left,category,flag);

        if(node->obj.getCategory() == category)
        {
            node->obj.print();
            flag= true;
        }

        SearchCategory(node->Right,category,flag);
    }
    // Performs in-order traversal of the BST and displays book titles in ascending order.
    void TraverseAsc (BSTNode* root)  // Left -> Root -> Right
    {
        if(root == nullptr) // tree is empty
            return;
        TraverseAsc(root->Left);
        root->obj.printTitle();
        TraverseAsc(root->Right);
    }
    // Performs reverse of in-order traversal of the BST and displays book titles in descending order.
    void TraverseDesc (BSTNode* root)  // Right -> Root -> Left
    {
        if(root == nullptr) // tree is empty
            return;
        TraverseDesc(root->Right);
        root->obj.printTitle();
        TraverseDesc(root->Left);
    }
    // Clear Helper function
    // Post order traversal (Left->Right->Root) and delete all the nodes in our BST
    void Clear (BSTNode* node)
    {
        if(node != nullptr)
        {
            if(node->Left != nullptr)
            {
                Clear(node->Left);   // Recursively start removing the left subtree
            }
            if(node->Right != nullptr)
            {
                Clear(node->Right);   // Recursively start removing the right subtree
            }
            delete node;
        }
    }
};
