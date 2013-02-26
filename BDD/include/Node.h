#ifndef Node_H
#define Node_H


class Node
{
    public:
        Node();
        Node(int i, Node* l, Node* r);
        Node* getLhs();
        Node* getRhs();
        void setLhs(Node* l);
        void setRhs(Node* r);
        int getIndice();
        void setIndice(int i);
        Node* getTrueNode();
        Node* getFalseNode();
        bool getValue();
        void setValue(bool val);
        bool isLeaf();
        void setLeaf(bool l);
        virtual ~Node();
    protected:
    private:
        Node* lhs; /* noeud si vrai */
        Node* rhs; /* noeud si faux */
        int indice;
        bool value;
        bool leaf;
};

#endif // Node_H
