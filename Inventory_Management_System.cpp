#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

class InventoryNode
{
    private:
        float price;
        int quantity;
        char category;
        int day, month, year;
        
    public:
        InventoryNode *left, *right;
        int code;
        InventoryNode(int c = 0, char stockCat = '-', int d = 0, int m = 0, int y = 0, float pri = 0.0, int quan = 0){
            code = c;
            category = stockCat;
            day = d;
            month = m;
            year = y;
            price = pri;
            quantity = quan;
        }
        char getStkCat(){
            return category;
        }
        int getDay(){
            return day;
        }
        int getMonth(){
            return month;
        }
        int getYear(){
            return year;
        }
        float getPrice(){
            return price;
        }
        int getQuantity(){
            return quantity;
        }
        void setSktCat(char a)
        {
            category = a;
        }
        void setDay(int b)
        {
            day = b;
        }
        void setMonth(int c)
        {
            month = c;
        }
        void setYear(int d)
        {
            year = d;
        }
        void setPrice(float e)
        {
            price = e;
        }
        void setQuantity(int f)
        {
            quantity = f;
        }
};


class Stack{
	public:
        InventoryNode *top;

		void createStack(){
			top = NULL;
		}
		
		bool isEmpty(){
			return (top == NULL);
		}
		
		void push(InventoryNode *ntopptr){
            InventoryNode *temp = new InventoryNode(ntopptr->code,ntopptr->getStkCat(),ntopptr->getDay(),ntopptr->getMonth(),ntopptr->getYear(),ntopptr->getPrice(),ntopptr->getQuantity());
            if(isEmpty())
            {
                temp->right = NULL;
                temp->left = NULL;
            }
            else
            {
                temp->right = top;
                temp->left = NULL;
            }
			top = temp;
		}
		
        void pop(){
            InventoryNode *delnode = top;
            
            if(isEmpty()){
                cout << "No more thing to undo\n";
            }
            else{
                top = top->right;
                delnode->right = NULL;
                delete delnode;
            }
        }
        
	    void clearStack(){
            InventoryNode*temp = top;
            if(isEmpty()){
                cout << "Message: Nothing to undo" << endl;
                return;
            }
            else
            {
                while(temp != NULL){
                top = temp->right;
                delete temp;
                temp = top;
                }
            }
	    }

        void printStack(){
            InventoryNode*temp = top;

            if(isEmpty()){
                cout << "Message: Nothing to delete/undo" << endl;
            }
            else{
                while(temp){
                    if(temp->getMonth() < 10)
                    {
                        cout << right << fixed << setprecision(2) << " " << setw(5)  << " " << setfill('0') << setw(4)  << temp->code << right << setfill(' ') << setw(20) << temp->getStkCat() << right << setfill(' ') << setw(18) << temp->getDay() << "/ " << temp->getMonth() << "/" << temp->getYear() << right << setfill(' ') << setw(25) << temp->getPrice() << right << setfill(' ')  << setw(15) << temp->getQuantity() << endl;
                    }
                    else
                    {
                        cout << right << fixed << setprecision(2) << " " << setw(5)  << " " << setfill('0') << setw(4)  << temp->code << right << setfill(' ') << setw(20) << temp->getStkCat() << right << setfill(' ') << setw(18) << temp->getDay() << "/" << temp->getMonth() << "/" << temp->getYear() << right << setfill(' ') << setw(25) << temp->getPrice() << right << setfill(' ')  << setw(15) << temp->getQuantity() << endl;
                    }
                    temp = temp->right;
                }
            }
            cout << "Total: " << countsize() << " Item(s)" << endl;
        }

        int countsize(){
            InventoryNode*temp = top;
            int count = 0;

            if(isEmpty()){
                return count;
            }
            else{
                while(temp){
                    temp = temp->right;
                    count++;
                }
                return count;
            }
        }
};

class TreeList
{
    private:
        InventoryNode *root;
        
    public:
        TreeList(){
            root = NULL;
        }

        bool isEmpty(){
            return root == NULL;
        }

        void insert(InventoryNode *&tree, int stkCode, char stkCat, int d, int m, int y, float pri ,int quan){
            if(tree == NULL){
                tree = new InventoryNode(stkCode, stkCat, d, m, y, pri, quan);
                tree->left = NULL;
                tree->right = NULL;
            }
            else if (stkCode < tree->code)
            {
                insert(tree->left, stkCode, stkCat, d, m, y, pri, quan);
            }
            else if (stkCode > tree->code)
            {
                insert(tree->right, stkCode, stkCat, d, m, y, pri, quan);
            }
        }

        void insertInventoryNode(int stkCode, char stkCat, int d, int m, int y, float pri , int quan){
            insert(root, stkCode, stkCat, d, m, y, pri, quan);
        }

        void GetSuccessor(InventoryNode *&tree, int &node, char &node2, int &node3,int &node4,int &node5,float &node6,int &node7,Stack undo)
        {
            if(tree->left == NULL)
            {
                node = tree->code;
                node2 = tree->getStkCat();
                node3 = tree->getDay();
                node4 = tree->getMonth();
                node5 = tree->getYear();
                node6 = tree->getPrice();
                node7 = tree->getQuantity();
                Delete(tree,node,undo);
            }
            else{
                GetSuccessor(tree->left,node,node2,node3,node4,node5,node6,node7, undo);
            }
        }

       void Delete(InventoryNode *&tree, int node, Stack undo)
       {
            if(tree == NULL)
            {
		    	cout << "\nError Message: Inventory Node not found" << endl;
            }
            else if(node < tree->code)
            {
                Delete(tree->left,node,undo);
            }
            else if(node > tree->code)
            {
                Delete(tree->right,node,undo);
            }
            else
            {
                DeleteNode(tree, undo);
            }
       }

        void DeleteNode(InventoryNode *&tree, Stack &undo)
        {
            int node,node3,node4,node5,node7;
            char node2;
            float node6;
            InventoryNode *tempPtr;
            tempPtr = tree;
            if(tree->left == NULL)
            {
                tree = tree->right;
                delete tempPtr;
            }
            else if(tree->right == NULL)
            {
                tree = tree->left;
                delete tempPtr;
            }
            else
            {
                GetSuccessor(tree->right, node, node2, node3, node4, node5, node6,node7, undo);
                tree->code = node;
                tree->setSktCat(node2);
                tree->setDay(node3);
                tree->setMonth(node4);
                tree->setYear(node5);
                tree->setPrice(node6);
                tree->setQuantity(node7);
            }
        }

        void undoStack(InventoryNode *& tree, int stkCode, Stack &undo){
            if (tree == NULL)
                return;
			else  if(stkCode < tree->code)       
		        // search the node on left subtree
		        undoStack(tree->left, stkCode, undo);
			else if(stkCode > tree->code)  
		        // search the node on right subtree
		        undoStack(tree->right, stkCode, undo);
		   	else{ 
                InventoryNode ntop = *tree;
                InventoryNode *ntopptr = &ntop;
                undo.push(ntopptr);
            }
        }

        void Undo(InventoryNode *& tree, Stack *undo){
            int count = 1;
            int stacksize = undo->countsize();
            int code, day, month, year, quantity;
            char Category;
            float price;

            do{
                cout << "Undo how many step(s)?";
                cin >> count;

                if(count>stacksize||count<0)
                    cout << "Error Message: Wrong Input, Enter Again!" << endl << endl;

            }while(count>stacksize||count<0);

            if(undo->top == NULL)
            {
                cout << "Nothing more to undo!" << endl;
            }

            for(int i=0; i<count;i++){
                if(undo->top){
                    code = undo->top->code;
                    Category = undo->top->getStkCat();
                    day = undo->top->getDay();
                    month = undo->top->getMonth();
                    year = undo->top->getYear();
                    price = undo->top->getPrice();
                    quantity = undo->top->getQuantity();

                    insertInventoryNode(code, Category, day, month, year, price , quantity);
                    undo->pop();
                }
            }
        }
		
		void deleteNode	(){
            int stkCode;
            Stack undo;
            bool con1 = true, con2 = false;
            int action;
            
            undo.createStack();

            while(con1){
                con1 = false;

                cout << "Enter product code to delete: ";
                cin >> stkCode; 

                undoStack(root, stkCode, undo);
                    
                Delete(root, stkCode, undo);

                cout << "\n========================================= << Delete List >> =======================================" << endl;
                cout << "Stock Code\t" <<"Stock Category\t" << "\tDate of Manufactured\t" << "\tPrice(RM)\t" << "Quantity" << endl;
                cout << "---------------------------------------------------------------------------------------------------" << endl;                    

                undo.printStack();

                do{
                    con2 = false;
                    cout << "\n(1). Delete additional stock.";
                    cout << "\n(2). Confirm to delete and exit.";
                    cout << "\n(3). Undo deletion.";
                    cout << "\n\nDecision: ";
                    cin >> action;

                    if(action == 1){
                        con1 = true;
                        system("CLS");
                    }
                    
                    else if(action == 2){
                        undo.clearStack();
                        system("CLS");
                    }
                    
                    else if(action == 3){
                        Undo(root, &undo);
                        system("CLS");
                        cout << "\n========================================= << Delete List >> =======================================" << endl;
                        cout << "Stock Code\t" <<"Stock Category\t" << "\tDate of Manufactured\t" << "\tPrice(RM)\t" << "Quantity" << endl;
                        cout << "---------------------------------------------------------------------------------------------------" << endl;                    

                        undo.printStack();
                        con2 = true;
                    }

                    else{
                        cout << "Invalid Option!" << endl;
                        con2 = true;
                    }
                }while(con2 == true);
            }
        }

    	void print(InventoryNode *tree){
            if(tree->getMonth() < 10)
            {
                cout << right << fixed << setprecision(2) << " " << setw(5)  << " " << setfill('0') << setw(4)  << tree->code << right << setfill(' ') << setw(20) << tree->getStkCat() << right << setfill(' ') << setw(18) << tree->getDay() << "/ " << tree->getMonth() << "/" << tree->getYear() << right << setfill(' ') << setw(25) << tree->getPrice() << right << setfill(' ')  << setw(15) << tree->getQuantity() << endl;
            }
            else
            {
                cout << right << fixed << setprecision(2) << " " << setw(5)  << " " << setfill('0') << setw(4)  << tree->code << right << setfill(' ') << setw(20) << tree->getStkCat() << right << setfill(' ') << setw(18) << tree->getDay() << "/" << tree->getMonth() << "/" << tree->getYear() << right << setfill(' ') << setw(25) << tree->getPrice() << right << setfill(' ')  << setw(15) << tree->getQuantity() << endl;
            }
        }

        void printtoFile(InventoryNode *tree, ofstream &output) // Designed to print tree to textfile
        {
            if(tree->getMonth() < 10)
            {
                output << right << fixed << setprecision(2) << " " << setw(5)  << " " << setfill('0') << setw(4)  << tree->code << right << setfill(' ') << setw(20) << tree->getStkCat() << right << setfill(' ') << setw(18) << tree->getDay() << "/ " << tree->getMonth() << "/" << tree->getYear() << right << setfill(' ') << setw(25) << tree->getPrice() << right << setfill(' ')  << setw(15) << tree->getQuantity() << endl;
            }
            else
            {
                output << right << fixed << setprecision(2) << " " << setw(5)  << " " << setfill('0') << setw(4)  << tree->code << right << setfill(' ') << setw(20) << tree->getStkCat() << right << setfill(' ') << setw(18) << tree->getDay() << "/" << tree->getMonth() << "/" << tree->getYear() << right << setfill(' ') << setw(25) << tree->getPrice() << right << setfill(' ')  << setw(15) << tree->getQuantity() << endl;
            }        
        }

		void printAll(InventoryNode *tree){
			if(tree){
				printAll(tree->left);
				print(tree);
				printAll(tree->right);
			}
		}

		void printAll2(InventoryNode *tree, ofstream& out){ // Designed to print tree to textfile
			if(tree){
				printAll2(tree->left,out);
				printtoFile(tree, out);
				printAll2(tree->right,out);
			}
		}

        void printCat(InventoryNode *tree, char cat){
			if(tree){
				printCat(tree->left,cat);
				
                if(tree->getStkCat() == cat)
                    print(tree);
				
                printCat(tree->right,cat);
			}
		}
        
       void printTreeOutput(ofstream& out) // Designed to print tree to textfile
        {
            printAll2(root,out);
        }

        void printTree(){
            int choice = 6;

            do{
                cout << "Which category you want to print?" << endl
                    << "(1). A" << endl
                    << "(2). B" << endl
                    << "(3). C" << endl
                    << "(4). D" << endl
                    << "(5). E" << endl
                    << "(6). All Categories" << endl
                    << "Enter option: ";
                cin >> choice;
                system("CLS");

                if(choice>=1 && choice<=6)
                {
                    cout << "\n====================================== << Inventory List >> ====================================" << endl;
                    cout << "\nStock Code\t" <<"Stock Category\t" << "\tDate of Manufactured\t" << "\tPrice(RM)\t" << "Quantity" << endl;
                    cout << "\n------------------------------------------------------------------------------------------------" << endl;                    
                }

                if(choice == 1)
                    printCat (root, 'A');
                
                else if(choice == 2)
                    printCat (root, 'B');
                
                else if(choice == 3)
                    printCat (root, 'C');
                
                else if(choice == 4)
                    printCat (root, 'D');
                
                else if(choice == 5)
                    printCat (root, 'E');
                
                else if(choice == 6)
                    printAll (root);
                
                else
                    cout << "Error Message: Invalid Option!" << endl << endl;

            }while(choice<1 || choice>6);
		}

        bool searchNodes(InventoryNode* tree, int num)
        {
            bool res1, res2;
            if (tree == NULL)
            {
                return false;
            }
        
            if (tree->code == num)
            {
                return true;
            }

            res1 = searchNodes(tree->left, num);
            if(res1)
            {
                return true;
            } 
            res2 = searchNodes(tree->right, num);
            if(res2)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        void insertAdditionalNode(TreeList *t)
        {
            float p; // price
            int q; // quantity
            char c; // category
            int d, m, y; // day month year
            int cd; // code

            do
            {
                if(t->searchNodes(t->root, cd))
                {
                    system("Color 4");
                    cout << "Error Message: The Product Code has already existed in the database. Please enter a valid Product Code." << endl << endl;
                    system("pause");
                }
                system("Color F");
                cout << "Enter the Product Code: ";
                cin >> cd;
            } while (t->searchNodes(t->root, cd));
            
            cout << "Enter the Product Category: ";
            cin >> c;
            cout << "\nEnter the Day (DD): ";
            cin >> d;
            cout << "\nEnter the Month (1-12): ";
            cin >> m;
            cout << "\nEnter the Year (YYYY): ";
            cin >> y;
            cout << "\nEnter the Product Price: ";
            cin >> p;
            cout << "\nEnter the Product Quantity: ";
            cin >> q;
            
            t->insertInventoryNode(cd, c, d, m, y, p, q);
        }
};

int main()
{
    TreeList tree;
    ifstream inputFile;
    ofstream outputFile;

    float p; // price
    int q; // quantity
    char c; // category
    int d, m, y; // day month year
    int cd; // code

    int menuOption;
    
    inputFile.open("InventoryList.txt");
    outputFile.open("SortedInventoryList.txt");
    if(!inputFile){
        cout << "Inventory List File was not found." << endl;
        system("pause");
        exit(0);
    }

    while(!inputFile.eof())
    {
        inputFile >> cd >> c >> d >> m >> y >> p >> q;
        tree.insertInventoryNode(cd, c, d, m, y, p, q);
    }

    do
    {
        cout << "\n=======================================<< Option Menu >> =======================================" << endl;
        cout << "\n1. Insert additional node into tree. ";
        cout << "\n2. Delete node from tree.";
        cout << "\n3. Display nodes.";
        cout << "\n4. Exit." << endl;
        cout << "Enter an option: ";
        cin >> menuOption;
        system("CLS");
        switch (menuOption)
        {
        case 1:
            tree.insertAdditionalNode(&tree);
            break;
        
        case 2:
            tree.deleteNode();
            break;

        case 3:
            tree.printTree();
            break;

        case 4:
            outputFile << "\n================================ << Sorted Inventory List >> ======================================" << endl;
            outputFile << "\nStock Code\t" <<"\tStock Category\t" << "\tDate of Manufactured\t" << "\tPrice(RM)\t" << "\tQuantity" << endl;
            outputFile << "\n--------------------------------------------------------------------------------------------------" << endl;
            tree.printTreeOutput(outputFile);
            cout << "Thank you for using the Inventory Management System!" << endl << endl;
            system("pause");
            exit(0);

        default:
            cout << "\nInvalid Menu Option." << endl;
            break;
        }
    } while (menuOption != 4);

    tree.printTreeOutput(outputFile);
    inputFile.close();
    system("pause");
    return 0;
}
