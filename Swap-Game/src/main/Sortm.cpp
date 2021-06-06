#include "Sort.h"
#include "TableauDynamique.h"
int count_ins = 0;

Sort::Sort()
{
  median = 0;
}
Sort::~Sort()
{
  median = 0;
    a.vider();
    b.vider();
}
int Sort::recupCount()
{
  int n=count_ins;
  count_ins=0;
  return n;
}
int Sort::get_median() const
{
  return median;
}
TableauDynamique Sort::get_tabA() const
{
  return a;
}
TableauDynamique Sort::get_tabB() const
{
  return b;
}
void Sort::set_median(int new_median)
{
  median = new_median;
}
void Sort::set_tabA(TableauDynamique new_A)
{
  for(int i = 0; i < a.taille_utilisee; i++)
  {
    a.ajouterElement(new_A.valeurIemeElement(i));
  }
}
void Sort::set_tabB(TableauDynamique new_B)
{
  for(int i = 0; i < new_B.taille_utilisee; i++)
  {
    b.ajouterElement(new_B.valeurIemeElement(i));
  }
}
int Sort::search_medianne(TableauDynamique tab)
{
    int median = 0;
    int i = 0;
    int j = 0;
    int count = 0;
    int check_pair = 0;
    if ((tab.taille_utilisee % 2) == 0)
    {
      check_pair  = tab.taille_utilisee/2;
    }
    else
    {
        check_pair  = (tab.taille_utilisee - 1)/2;
    }
    while (i < tab.taille_utilisee)
    {
      while (j < tab.taille_utilisee)
      {
        if(tab.valeurIemeElement(i) > tab.valeurIemeElement(j))
        {
          count++;
        }
        if(count == check_pair  && j == (tab.taille_utilisee - 1))
        {
          median = tab.valeurIemeElement(i);
        }
        j++;
      }
      j = 0;
      count = 0;
      i++;
    }
    return median;
}

/*void Sort::pb_apply(TableauDynamique & a,TableauDynamique & b,TableauDynamique  index_before,TableauDynamique index_after)
{
  if (index_before.valeurIemeElement(0))
}*/
/*TableauDynamique Sort::index_of_elem_before_middle(TableauDynamique & tab, int median)
{
  TableauDynamique index;
  int i = 0;
  while (i < tab.taille_utilisee/2)
  {
    cout << tab.valeurIemeElement(i) << endl;
    if (tab.valeurIemeElement(i) < median)
    {
      index.ajouterElement(i);
    }
    i++;
  }
  return (index);
}
TableauDynamique Sort::index_of_elem_after_middle(TableauDynamique & tab, int median)
{
  TableauDynamique index;
  int i = tab.taille_utilisee/2;
  while (i < tab.taille_utilisee)
  {
    if (tab.valeurIemeElement(i) < median)
    {
      index.ajouterElement(i);
    }
    i++;
  }
  return (index);
}
*/
//function to sort three elements
int Sort::calcul_min(TableauDynamique tab)
{
  int min;
  int i = 0;
  int j = 0;
  int count = 0;
  while (i < tab.taille_utilisee)
  {
    while (j < tab.taille_utilisee)
    {
      if(tab.valeurIemeElement(i) < tab.valeurIemeElement(j))
      {
        count++;
      }
      if(count == (tab.taille_utilisee - 1)  && j == (tab.taille_utilisee - 1))
      {
        min = tab.valeurIemeElement(i);
      }
      j++;
    }
    j = 0;
    count = 0;
    i++;
  }
  return min;

}
// verify if the array is already sorted
int Sort::if_sorted(TableauDynamique & a)
{
  int i = 0;
  while (i < a.taille_utilisee - 1)
  {
    if (a.valeurIemeElement(i) > a.valeurIemeElement(i + 1))
    {
      return 0;
    }
    i++;
  }
  return 1;
}
// verify if the array is already sorted up to a certain element

int Sort::if_sorted_upTo_size(TableauDynamique & a, int size)
{
  int i = 0;
  while (i < size)
  {
    if (a.valeurIemeElement(i) > a.valeurIemeElement(i + 1))
    {
      return 0;
    }
    i++;
  }
  return 1;
}
void Sort::sort_array_for_three(TableauDynamique & tab)
{

  if(tab.valeurIemeElement(0) > tab.valeurIemeElement(2) &&  tab.valeurIemeElement(1) <  tab.valeurIemeElement(0))
  {
    ra(tab);
    count_ins++;
    cout << "ra" << endl;
  }
  else if(tab.valeurIemeElement(0) > tab.valeurIemeElement(tab.taille_utilisee - 1))
  {
    rra(tab);
    count_ins++;
    cout << "rra"  << endl;

  }
  if(tab.valeurIemeElement(0) > tab.valeurIemeElement(1))
  {
    sa(tab);
    count_ins++;
    cout << "sa"  << endl;

  }
  else if (tab.valeurIemeElement(0) < tab.valeurIemeElement(1) && tab.valeurIemeElement(1) > tab.valeurIemeElement(2))
  {
    rra(tab);
    count_ins++;
    cout << "rra"  << endl;

    sa(tab);
    count_ins++;
    cout << "sa"  << endl;
  }
}
//conditions for pb/pa
void Sort::apply_pb(TableauDynamique & a,TableauDynamique & b,int median)
{

  while ((median > a.valeurIemeElement(0)))
   {
     pa(a, b);
     count_ins++;
     cout << "p..b"  << endl;
   }
   if(if_sorted_upTo_size(a, a.taille_utilisee - 2) && !if_sorted_upTo_size(b, b.taille_utilisee - 2))
   {
     rrr(a,b);
     count_ins++;
     cout << "rrr" << endl;
   }
   if(b.valeurIemeElement(0) < b.valeurIemeElement(b.taille_utilisee-1) && a.valeurIemeElement(0) > a.valeurIemeElement(b.taille_utilisee-1) &&  b.taille_utilisee != 2)
   {
     rr(b, a);
     count_ins++;
     cout << "rr"  << endl;
   }
   if(b.valeurIemeElement(0) < b.valeurIemeElement(b.taille_utilisee-1) && b.taille_utilisee != 2)
   {
     ra(b);
     count_ins++;
     cout << "rB" << endl;
   }
   if(b.valeurIemeElement(0) < b.valeurIemeElement(1) && a.valeurIemeElement(0) > a.valeurIemeElement(1))
   {
     ss(a, b);
     count_ins++;
     cout << "ss"  << endl;
   }

}
//all the conditions to sort before  free elements
void Sort::instructions_before_three_elem(TableauDynamique & tab_A,TableauDynamique & tab_B, int median)
{
  TableauDynamique tab_verif;

  for(int i=2;i<tab_A.taille_utilisee;i++)
  {
    tab_verif.ajouterElement(tab_A.valeurIemeElement(i));
  }
  if(tab_A.valeurIemeElement(0) > tab_A.valeurIemeElement(1) && if_sorted(tab_verif))
  {
    sa(tab_A);
    count_ins++;
    cout << "sa"  << endl;
  }
/*  if(tab_A.valeurIemeElement(0) > tab_A.valeurIemeElement(1) && tab_A.valeurIemeElement(2) > tab_A.valeurIemeElement(3))
  {
    pa(tab_A,tab_B);
    pa(tab_A,tab_B);
    ss(tab_A,tab_B);
    count_ins =  count_ins + 3;
    cout<< "pb,pb,ss" << endl;
  }
*/
  if(tab_A.valeurIemeElement(tab_A.taille_utilisee - 1) < tab_A.valeurIemeElement(0) && tab_A.valeurIemeElement(tab_A.taille_utilisee - 1) != median
   && tab_A.valeurIemeElement(0) < tab_A.valeurIemeElement(1) && tab_A.valeurIemeElement(tab_A.taille_utilisee - 1) < tab_A.valeurIemeElement(tab_A.taille_utilisee - 2))
  {
    rra(tab_A);
    count_ins++;
    cout << "rrA" << endl;
  }

  if(b.valeurIemeElement(0) < b.valeurIemeElement(1) && b.valeurIemeElement(0) < b.valeurIemeElement(b.taille_utilisee-1))
  {
    ra(b);
    count_ins++;
    cout << "Rb" << endl;
  }
  int idiot=b.valeurIemeElement(1);
  int i=0;

  while(b.valeurIemeElement(0) < idiot && b.valeurIemeElement(0) > b.valeurIemeElement(b.taille_utilisee-1))
  {
    i++;
    rra(b);
    count_ins++;
    cout << "rrb"<<endl;
    sa(b);
    count_ins++;
    cout << "sb"<<endl;
    if(b.valeurIemeElement(0) < b.valeurIemeElement(b.taille_utilisee-1))
    {
      i++;
    }
  }
  while(i>0)
  {
    ra(b);
    count_ins++;
    cout << "r_b"<<endl;
    i--;
  }

  if(median == tab_A.valeurIemeElement(0))
  {
    ra(tab_A);
    count_ins++;
    cout << "rA"<<endl;
  }
/*  if (tab_A.valeurIemeElement(tab_A.taille_utilisee - 1) == median)
  {
    rra(tab_A);
    count_ins++;
    cout << "rra" << endl;
    pa(tab_A,tab_B);
    count_ins++;
    cout << "pb" << endl;
  }*/
  while (tab_A.valeurIemeElement(0) > median)
  {
    ra(tab_A);
    count_ins++;
    cout << "ra" << endl;
  }

  if (tab_B.valeurIemeElement(0) > tab_A.valeurIemeElement(0) &&
  tab_B.valeurIemeElement(1) < tab_A.valeurIemeElement(0) && tab_A.valeurIemeElement(1) > tab_A.valeurIemeElement(0))
  {
    pa(tab_A,tab_B);
    count_ins++;
    cout << "pB" << endl;

    sa(tab_B);
    count_ins++;
    cout << "sb" << endl;//rb avant
  }
  if (tab_B.valeurIemeElement(0) > tab_A.valeurIemeElement(0) &&
  tab_B.valeurIemeElement(1) > tab_A.valeurIemeElement(0) && tab_B.valeurIemeElement(2) < tab_A.valeurIemeElement(0)
   && tab_B.taille_utilisee>2)
  {
    pa(tab_B,tab_A);
    count_ins++;
    cout << "pa" << endl;
    sa(tab_A);
    count_ins++;

    cout << "sa" << endl;
  }
  if(tab_A.valeurIemeElement(0) < median && tab_A.valeurIemeElement(0) > tab_A.valeurIemeElement(1) && tab_B.valeurIemeElement(0) > tab_A.valeurIemeElement(0))
  {
    pa(tab_A,tab_B);
    count_ins++;
    cout << "p-b"  << endl;
  }
  if(tab_B.valeurIemeElement(0) < tab_B.valeurIemeElement(1))
  {
    sa(tab_B);
    count_ins++;
    cout << "s.b"  << endl;
  }
  if(tab_A.valeurIemeElement(0) > tab_A.valeurIemeElement(1) && tab_A.valeurIemeElement(0) < median && tab_A.valeurIemeElement(1) < median)
  {
    pa(tab_A,tab_B);
    count_ins++;
    cout << "pb"  << endl;
  }
  if(tab_A.valeurIemeElement(0) > tab_A.valeurIemeElement(1))
  {
    sa(tab_A);
    count_ins++;
    cout << "s..a"  << endl;
  }

}
//condtions for B
void Sort::instructions_for_B(TableauDynamique & tab_A,TableauDynamique & tab_B)
{
  if(tab_B.valeurIemeElement(0) < tab_B.valeurIemeElement(1) &&
   tab_B.valeurIemeElement(0) > tab_B.valeurIemeElement(tab_B.taille_utilisee -1) && tab_B.valeurIemeElement(0) > tab_B.valeurIemeElement(2))
  {
    sa(tab_B);
    count_ins++;
    cout << "sb" << endl;
  }
}

//case when we have four elements almost sorted
int Sort::four_elem(TableauDynamique & a)
{
  if (a.taille_utilisee == 4)
  {
    ra(a);
    cout << "ra" << endl;
  }
  return (if_sorted(a));
}
//recursive function
void Sort::sort_array(TableauDynamique & a, int median)
{
  static int  h = 1;
  static int taillePrem = a.taille_utilisee;
  h = h*2;
  int C = 0;
  for(int i = 2; i <= h; i= i * 2)
  {
    C = C + taillePrem/i;
  }
  if (a.taille_utilisee == 3)
  {
    sort_array_for_three(a);
    while(b.taille_utilisee>0)
    {
       pa(b,a);
       std::cout << "pa" << '\n';
       count_ins++;
    }
    cout << "nombres instructions = "<<count_ins << endl;
    return;
  }

  int i = 0;
  median = search_medianne(a);
  cout <<"median: " <<median<<endl;


  int y = 1;
  int count_B = b.taille_utilisee / 2;
  cout << "marime B: " << b.taille_utilisee << endl;
  while(b.taille_utilisee != C || four_elem(a))
  {
      y++;

      if (if_sorted(a))
      {
        while(b.taille_utilisee>0)
        {
           pa(b,a);
           count_ins++;
        }
        cout << "nombres instructions = "<<count_ins << endl;
        return;
      }
      instructions_before_three_elem(a,b,median);
      if (if_sorted(a))
      {
        while(b.taille_utilisee>0)
        {
           pa(b,a);
           cout << "pa" << endl;
           count_ins++;
        }
        cout << "nombres instructions = "<<count_ins << endl;
        return;
      }
      apply_pb(a,b, median);
      if (if_sorted(a))
      {
        while(b.taille_utilisee>0)
        {
           pa(b,a);
           count_ins++;
        }
        cout << "nombres instructions = "<<count_ins << endl;
        return;
      }
      instructions_for_B(a,b);

    cout << "B: ";
    b.afficher();
    cout << "A: ";
    a.afficher();
  }
  sort_array(a,median);
//  b.afficher();
//  tab.afficher();
}
