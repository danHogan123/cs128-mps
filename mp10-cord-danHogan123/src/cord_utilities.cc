#include "cord_utilities.hpp"
#include "string_view"

SharedPointer<Cord> ConcatCords(const SharedPointer<Cord>& left_cord,
                                const SharedPointer<Cord>& right_cord)
{
    if (left_cord.Get() == nullptr || right_cord.Get() == nullptr)
    {
        throw std::invalid_argument("");
    }
    Cord* cord = new Cord();
    cord->length_ = left_cord->length_ + right_cord->length_;
    cord->data_ = nullptr;

    cord->left_ = SharedPointer<Cord>(left_cord);
   // std::cout << cord->left_->data_ << std::endl;

    cord->right_ = SharedPointer<Cord>(right_cord);
   // std::cout << cord->right_->data_ << std::endl;
       
    SharedPointer<Cord> ret(cord);

    return ret;
}

SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord,
                              unsigned int lower_idx,
                              unsigned int upper_idx)
{
    SharedPointer<Cord> to_return;

    if (lower_idx<0 || upper_idx >curr_cord->Length()){throw std::invalid_argument("");}
    std::string str = curr_cord->StringHelp();
        
    if (lower_idx == 0 && upper_idx == curr_cord->Length()) return curr_cord;

    if (curr_cord->data_!=nullptr && curr_cord->Data()[0] != '\0')
    {
    SharedPointer<Cord> temp(new Cord(curr_cord->Data().substr(lower_idx, upper_idx - lower_idx)));
    return temp;
    }

    if (upper_idx <= curr_cord->Left()->Length()) 
    {
        to_return = SubString(curr_cord->Left(), lower_idx, upper_idx);
    } 
    else if (lower_idx >= curr_cord->Left()->Length()) 
    {
        to_return = SubString(curr_cord->Right(), lower_idx - curr_cord->Left()->Length(),
                                    upper_idx - curr_cord->Left()->Length());
    }
    else 
    {
        to_return = ConcatCords(SubString(curr_cord->Left(), lower_idx, curr_cord->Left()->Length()),
                                SubString(curr_cord->Right(), 0, upper_idx - curr_cord->Left()->Length()));
    }

    return to_return;
}
