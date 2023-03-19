/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PMergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:01:47 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/19 06:51:49 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PMergeMe.hpp"

PMergeMe::PMergeMe( void ) {}

PMergeMe::PMergeMe( PMergeMe const & p ) { (void) p; }

PMergeMe &PMergeMe::operator=( PMergeMe const & p ) { (void) p; return (*this); }

PMergeMe::~PMergeMe( void ) {}

// utils
void	PMergeMe::_sort( std::vector<int> & vect,
	int begin, int end )
{
	int mid;
	int val;
	
	int	i;
	int	j;
	int	k;
	
	int	lim;
	int shifts;
	
	if (end - begin > 2) // split of merge sort
	{
		mid = (end - begin) / 2;
		_sort (vect, begin, begin + mid);
		_sort (vect, begin + mid, end);
	}
	if (begin != 0 && end - begin == 2) // override begin and end if not start
	{
		begin /= 2;
		end = begin + 2;
	}
	if (end - begin == 2) // sort pairs, keep smaller number, push greater to the back of the vector
	{
		if (vect[begin] > vect[begin + 1])
		{
			val = vect[begin];
			vect.erase (vect.begin () + begin);
		}
		else
		{
			val = vect[begin + 1];
			vect.erase (vect.begin () + begin + 1);
		}
		vect.push_back (val);
	}

	if (end - begin == (int) vect.size ()) // finally ...
	{
		if (vect.size () % 2 == 1) // if size is odd, move single elem to the back
		{
			val = vect[vect.size () / 2];
			vect.erase (vect.begin () + vect.size () / 2);
			vect.push_back (val);
		}
		i = 0;
		while (++i < (int) vect.size () / 2) // order sub vectors
		{
			k = i;
			j = k - 1;
			while (j >= 0)
			{
				if (vect[k] < vect[j])
				{
					val = vect[k];
					vect[k] = vect[j];
					vect[j] = val;
					mid = (int) vect.size () / 2;
					val = vect[k + mid];
					vect[k + mid] = vect[j + mid];
					vect[j + mid] = val;
					k = j;
				}
				j--;
			}
		}

		shifts = 0;
		i = vect.size () / 2 + shifts;
		while (i < (int) vect.size ()) // binary-search insertion until pair in main chain
		{ 	
			// chain and also insert the number with highest len to insertion cost, ie most pricy insertion get done first
			lim = i - vect.size () / 2 - shifts;
			if (vect.size () % 2 == 1 && i == (int) vect.size () - 1)
				lim = 0;
			j = i - 2;
			while (j >= lim)
			{
				if (vect[i] <= *std::min_element (vect.begin (), vect.end ()))
				{
					shifts++;
					val = vect[i];
					vect.erase (vect.begin () + i);
					vect.insert (vect.begin (), val);
					break ;
				}
				else if (vect[i] >= vect[j] && vect[i] <= vect[j + 1])
				{
					val = vect[i];
					vect.erase (vect.begin () + i);
					vect.insert (vect.begin () + j + 1, val);
					shifts++;
					break ;
				}
				j--;
			}
			i++;
		}
	}
}

int PMergeMe::_at ( std::list<int> & li, int index )
{
	std::list<int>::iterator it;

	it = li.begin ();
	std::advance (it, index);
	return (*it);
}

void PMergeMe::_assign ( std::list<int> & li, int index, int val )
{
	std::list<int>::iterator it;

	it = li.begin ();
	std::advance (it, index);
	*it = val;
}

std::list<int>::iterator PMergeMe::_it ( std::list<int> & li, int index )
{
	std::list<int>::iterator it;

	it = li.begin ();
	std::advance (it, index);
	return (it);
}

void	PMergeMe::_sort( std::list<int> & vect,
	int begin, int end )
{
	int mid;
	int val;
	
	int	i;
	int	j;
	int	k;
	
	int	lim;
	int shifts;

	if (end - begin > 2) // split of merge sort
	{
		mid = (end - begin) / 2;
		_sort (vect, begin, begin + mid);
		_sort (vect, begin + mid, end);
	}
	if (begin != 0 && end - begin == 2) // override begin and end if not start
	{
		begin /= 2;
		end = begin + 2;
	}
	if (end - begin == 2) // sort pairs, keep smaller number, push greater to the back of the vector
	{
		if (_at (vect, begin) > _at(vect, begin + 1))
		{
			val = _at (vect, begin);
			vect.erase (_it (vect, begin));
		}
		else
		{
			val = _at (vect, begin + 1);
			vect.erase (_it (vect, begin + 1));
		}
		vect.push_back (val);
	}
	if (end - begin == (int) vect.size ()) // finally ...
	{

		if (vect.size () % 2 == 1) // if size is odd, move single elem to the back
		{
			val = _at (vect, vect.size () / 2);
			vect.erase (_it (vect, vect.size () / 2));
			vect.push_back (val);
		}
		i = 0;
		while (++i < (int) vect.size () / 2) // order sub vectors
		{
			k = i;
			j = k - 1;
			while (j >= 0)
			{
				if (_at (vect, k) < _at (vect, j))
				{
					val = _at (vect, k);
					_assign (vect, k, _at (vect, j));
					_assign (vect, j, val);
					mid = (int) vect.size () / 2;
					val = _at (vect, k + mid);
					_assign (vect, k + mid, _at (vect, j + mid));
					_assign (vect, j + mid, val);
					k = j;
				}
				j--;
			}
		}
		shifts = 0;
		i = vect.size () / 2 + shifts;
		while (i < (int) vect.size ()) // binary-search insertion until pair in main
		{ 	
			// chain and also insert the number with highest len to insertion cost, ie most pricy insertion get done first
			lim = i - vect.size () / 2 - shifts;
			if (vect.size () % 2 == 1 && i == (int) vect.size () - 1)
				lim = 0;
			j = i - 2;
			while (j >= lim)
			{
				if (_at (vect, i) <= *std::min_element (vect.begin (), vect.end ()))
				{
					shifts++;
					val = _at (vect, i);
					vect.erase (_it (vect, i));
					vect.insert (vect.begin (), val);
					break ;
				}
				else if (_at (vect, i) >= _at (vect, j)
					&& _at (vect, i) <= _at (vect, j + 1))
				{
					val = _at (vect, i);
					vect.erase (_it (vect, i));
					vect.insert (_it (vect, j + 1), val);
					shifts++;
					break ;
				}
				j--;
			}
			i++;
		}
	}
}

int PMergeMe::sort ( char **args )
{
	clock_t				data_man_start;
	clock_t				data_man_end;
	
    clock_t 			start_vect;
	std::vector<int> 	vect;
    clock_t 			end_vect;
		
    clock_t 			start_list;
	std::list<int> 		li;
    clock_t 			end_list;
	
	bool				s;

	std::cout << "Before: [";
    data_man_start = clock();
	while (*args)
	{
		if (vect.size () > 0)
			std::cout << " ";
		std::cout << *args;
		vect.push_back ( std::stoi (*args) );
		li.insert (li.end (), std::stoi (*args) );
		args++;
	}
	std::cout << "]" << std::endl;
	data_man_end = clock ();

	start_vect = clock ();
	_sort (vect, 0, vect.size ());
    end_vect = clock();
	
	start_list = clock ();
	_sort (li, 0, vect.size ());
    end_list = clock();

	std::cout << "After (std::vector): [";
	for (std::vector<int>::iterator it = vect.begin (); it < vect.end (); it++)
	{
		if (it - vect.begin () > 0)
			std::cout << " ";
		std::cout << *it;
	}
	std::cout << "] => " << (static_cast<float>(end_vect - start_vect + data_man_end - data_man_start) / CLOCKS_PER_SEC * 1000000) << " us ";
	if (std::is_sorted (vect.begin (), vect.end ()))
		std::cout << "ok";
	else
		std::cout << "ko";
	std::cout << std::endl;
	std::cout << "After (std::list): [";
	s = false;
	while (li.size () > 0)
	{
		if (!s)
			s = true;
		else
			std::cout << " ";
		std::cout << li.front ();
		li.pop_front ();
	}
	std::cout << "] => " << (static_cast<float>(end_list - start_list + data_man_end - data_man_start) / CLOCKS_PER_SEC * 1000000) << " us ";
	if (std::is_sorted (li.begin (), li.end ()))
		std::cout << "ok";
	else
		std::cout << "ko";
	std::cout << std::endl;
	return (0);
}
