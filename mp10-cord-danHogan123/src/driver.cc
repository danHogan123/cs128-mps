#include <iostream>

#include "cord_utilities.hpp"
#include "cord.hpp"

int main() {


SharedPointer<Cord> he = new Cord("he");
SharedPointer<Cord> llo = new Cord("llo");
SharedPointer<Cord> hello= ConcatCords(he,llo);
std::cout << hello->ToString().Get() << std::endl;


SharedPointer<Cord> wor = new Cord("wor");
SharedPointer<Cord> ld = new Cord("ld");
SharedPointer<Cord> world = ConcatCords(wor,ld);
std::cout << world->ToString().Get() << std::endl;

SharedPointer<Cord> hello_world = ConcatCords(hello,world);



auto temp = SubString(hello_world,2,9);

std::cout << hello_world->ToString().Get() << std::endl;
std::cout << temp->ToString().Get() << std::endl;


















  //std::cout << "hi" << std::endl;

//  SharedPointer<Cord> a = new Cord("CS_");

//  auto a_st = a->ToString();

//   std::cout << a_st.Get() <<a->Length()<< std::endl;



//  SharedPointer<Cord> b = new Cord("128_");
//  SharedPointer<Cord> c = ConcatCords(a, b);

//  //auto s = a->ToString();
// auto c_str = c->ToString();
 
 
//   std::cout  << c_str.Get() << std::endl;

//   SharedPointer<Cord> k = new Cord("butt");
//  SharedPointer<Cord> f = new Cord("poop");
//  SharedPointer<Cord> d = ConcatCords(k,f);
//  auto d_str = d->ToString();
// //auto p = d->ToString();
//   // auto d_str = d->ToString();
//    std::cout <<  d_str.Get() << std::endl;

//    SharedPointer<Cord> pie = ConcatCords(c,d);

//    auto yum = pie->ToString();
 
 
//   std::cout  << yum.Get() << std::endl;

  // auto res = SubString(c, 0, 3);
  // auto res_str = res->ToString();
  // std::cout << res_str.Get() << std::endl;
}



// std::cout << "next" << std::endl;
// SharedPointer<Cord> k = new Cord("butt");
//  SharedPointer<Cord> f = new Cord("poop");
//  SharedPointer<Cord> d = ConcatCords(k,f);

// SharedPointer<Cord> hi = ConcatCords(c,d);

// int main() {
//   //std::cout << "hi" << std::endl;
//  SharedPointer<Cord> a = new Cord("CS_");
//   //std::cout << "hi" << std::endl;
//  SharedPointer<Cord> b = new Cord("128_");
//  SharedPointer<Cord> c = ConcatCords(a, b);
//   auto c_str = c->ToString();}