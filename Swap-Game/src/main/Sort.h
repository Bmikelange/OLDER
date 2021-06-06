#ifndef _SORT_H
#define _SORT_H
#include "TableauDynamique.h"
#include "ElementTD.h"
#include "push_swap.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

class Sort : public niveau
{
private:
  int median;
  TableauDynamique a;
  TableauDynamique b;

public:
  Sort();
  ~Sort();
  int get_median() const;
  TableauDynamique get_tabA() const;
  TableauDynamique get_tabB() const;
  void set_median(int mediana);
  void set_tabA(TableauDynamique new_A);
  void set_tabB(TableauDynamique new_B);

  int recupCount();
  int search_medianne(TableauDynamique tab);
  void apply_pb(TableauDynamique & a,TableauDynamique & b,int median);
  void sort_array(TableauDynamique & tab, int median);
  void sort_array_for_three(TableauDynamique & tab, TableauDynamique & b, int median);
  void instructions_before_three_elem(TableauDynamique & tab, TableauDynamique & tab_B, int median);
  TableauDynamique index_of_elem_before_middle(TableauDynamique & tab, int median);
  TableauDynamique index_of_elem_after_middle(TableauDynamique & tab, int median);
  void instructions_for_B(TableauDynamique & tab_A,TableauDynamique & tab_B);
  int if_sorted(TableauDynamique & a);
  int if_sorted_rev(TableauDynamique & a);
  int four_elem(TableauDynamique & a);
  int calcul_min(TableauDynamique tab);
  void backtraking_Sort(TableauDynamique  tab_A, TableauDynamique  tab_B);
  int if_sorted_upTo_size(TableauDynamique & a, int size);






};


#endif
