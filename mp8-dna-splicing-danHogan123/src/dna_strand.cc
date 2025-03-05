#include "dna_strand.hpp"
#include <stdexcept>

    DNAstrand::~DNAstrand()
    {
        while (head_ !=nullptr)
        {
            Node* next = head_->next;
            delete head_;
            head_ = next;
        }
    }

    unsigned int DNAstrand::SizeOf(const char* pattern)
    {
        unsigned int count = 0;
        int i = 0;
        while(pattern[i] != '\0')
        {
            count++;
            i++;
        }
        return count;
    }

    unsigned int DNAstrand::SizeOf(DNAstrand& to_splice_in)
    {
        unsigned int count = 0;
        Node* curr = to_splice_in.head_;
        while (curr!= nullptr)
        {
            count++;
            curr = curr->next;
        }
        return count;
    }


    bool DNAstrand::Verify(const char* pattern, unsigned int current)
    {
        Node* now = head_;
        bool verify = true;
        unsigned int count = 0;

        while( now != nullptr && count != current)
        {  
            count++;
            now = now->next;
        }

        for ( unsigned int i = 0; i < SizeOf(pattern); ++i)
        {
            if (pattern[i] != now->data)
                verify = false;
            now = now->next;
        }

        return verify;
    }


    unsigned int DNAstrand::Occurances(const char* pattern)
    {
        unsigned int num =0;
        unsigned int occurances =0;
        Node* loop = head_;
        bool count = true;
        unsigned int size = SizeOf(*this);

        for (unsigned int i=0; i< size-1; ++i)
        { 
            Node* nest = loop;

                for (unsigned int j=0; j< SizeOf(pattern); ++j)
                { 
                    count = true;
                    if (pattern[j] != nest->data)
                    {
                        count = false;
                        break;
                        
                    }
                    nest = nest->next;
                }
            num++;
            if(count){occurances++;}
            loop = loop->next;
            
        }
        return occurances;
    }


    void DNAstrand::FindIndex(const char* pattern, Node*& curr, unsigned int& current_idx)
    {
        unsigned int occurances = Occurances(pattern);
        unsigned int occ_cnt=0;

        while (curr != nullptr)
        {
            if( Verify(pattern,current_idx)){
                occ_cnt++;
                if(occ_cnt == occurances)
                    break;
            }
            if(current_idx == 0){
                current_idx ++;
                continue;
            } 
            current_idx ++;
            curr = curr->next; 

            if (SizeOf(pattern)==1 && pattern[0]==curr->data) {break;}   
            if (current_idx+SizeOf(pattern) > SizeOf(*this)) {throw std::invalid_argument("pattern not found");}
        }   
    }
    

    void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in)
    {
        if (SizeOf(*this) < SizeOf(pattern)) {throw std::invalid_argument("pattern not found");}
        if (&to_splice_in == this) {return;}
        if (SizeOf(pattern) == 0 || SizeOf(to_splice_in) == 0) {return;}

        Node* curr = head_;
        unsigned int current_idx = 0;
        FindIndex(pattern,curr,current_idx);

        if (current_idx == 0)
        {
            FromHead(pattern,curr);
            to_splice_in.tail_->next =curr;
            head_ = to_splice_in.head_;
        } 
        else if (current_idx + SizeOf(pattern) > SizeOf(*this))
        {
            FromTail(pattern,curr);
            tail_->next = to_splice_in.head_;
            tail_ = to_splice_in.tail_;
        } 
        else 
        {
            Node* end = nullptr;
            FillEnd(current_idx, end, SizeOf(pattern)-1);
            FromMiddle(pattern,curr);
            to_splice_in.tail_->next = end;
            curr->next = to_splice_in.head_;
        }

        to_splice_in.head_ = to_splice_in.tail_ = nullptr;
    }


    void DNAstrand::FromHead(const char* pattern, Node*& curr)
    {
        for(unsigned int i = 0; i < SizeOf(pattern); ++i)
        {
            curr = curr->next;
            delete head_;
            head_ = curr;
        }
    }


    void DNAstrand::FromTail(const char* pattern, Node*& curr)
    {
        if(SizeOf(pattern)==1)
        {
            Node* weird = head_;

            while(weird->next->next != nullptr)
                weird = weird->next;

            delete tail_;
            tail_ = weird;
        }
        
        else
        {
            for(unsigned int i = 0; i < SizeOf(pattern); ++i)
            {
                Node* rem = curr->next;
                curr->next = rem->next;
                delete rem;
            }
        }
    }


    void DNAstrand::FromMiddle(const char* pattern, Node*& curr)
    {
        for(unsigned int i = 0; i < SizeOf(pattern); ++i)
        {
            Node* rem = curr->next;
            curr->next = rem->next;
            delete rem;
        }
    }


    void DNAstrand::FillEnd(unsigned int& current_idx, Node*& end, unsigned int size_pattern)
    {
        Node* curr = head_;
        for (unsigned int i=0; i< (current_idx+size_pattern)+1; ++i)
        {
            curr = curr->next;
        }
        end = curr;
    }


// void DNAstrand::WriteIt(const DNAstrand& dna)
// {
//      unsigned int t = 0;
//      Node* x = dna.head_;
//      while(x != nullptr){
//         std::cout << x->data;
//         x = x->next;
//         t++;
//      }
//      std::cout << '\n' << std::endl;

//  }


  DNAstrand::DNAstrand(const char* dna)
  {
    head_  = new Node(dna[0]);
    Node* curr = head_;
    for(unsigned int i = 1; i < SizeOf(dna); ++i)
    {
        Node* node = new Node(dna[i]);
        curr->next = node;
        curr = curr->next;
    }
    tail_ = curr;
    tail_->next = nullptr;
  }