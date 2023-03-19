/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:56:39 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/19 06:46:51 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/**
 * Date class
 */
// default constructor
	Date::Date( void ): _year(0), _month(0), _day(0), _date("") {}

// custom constructor which takes in date in string format
	Date::Date( std::string s )
	{
		size_t	pos;

		_date = s;
		_year = 0;
		_month = 0;
		_day = 0;
		pos = s.find ("-");
		while (_year == 0 || _month == 0 || _day == 0)
		{
			if (_year == 0)
				_year = stoi (s.substr (0, pos));
			else if (_month == 0)
				_month = stoi (s.substr (0, pos));
			else
				_day = stoi (s.substr (0, pos));
			if (pos == std::string::npos)
				break ;
			s = s.substr (pos + 1);
			pos = s.find ("-");
		}
	}

// copy member funcs
Date::Date( const Date & d ): _year(d.getYear ())
	, _month(d.getMonth ()), _day(d.getDay ()), _date(d.getDate ()) {}

Date &Date::operator=( const Date & d )
{
	if (this == &d)
		return (*this);
	_year = d.getYear ();
	_month = d.getMonth ();
	_day = d.getDay ();
	_date = d.getDate ();
	return (*this);
}

Date::~Date( void ) {}

// getters
const int &Date::getYear( void ) const { return (_year); }

const int &Date::getMonth( void ) const { return (_month); }

const int &Date::getDay( void ) const { return (_day); }

const std::string &Date::getDate( void ) const { return (_date); }

// overloaded operators for std::map sorting
bool Date::operator==( const Date & d ) const
{
	if (_year == d.getYear ()
		&& _month == d.getMonth ()
		&& _day == d.getDay ())
		return (true);
	return (false);
}

bool Date::operator< ( const Date & d ) const
{
	if (_year == d.getYear ())
	{
		if (_month == d.getMonth ())
		{
			if (_day < d.getDay ())
				return (true);
			return (false);
		}
		else if (_month < d.getMonth ())
			return (true);
		else
			return (false);
	}
	else if (_year < d.getYear ())
		return (true);
	else
		return (false);
}

bool Date::operator> ( const Date & d ) const
{
	return (!(*this < d) && !(*this == d));
}

std::ostream & operator << ( std::ostream & stream, const Date & d )
{
	stream << d.getDate ();
	return (stream);
}
/**
 * BitcoinExchange static class
 */	
BitcoinExchange::BitcoinExchange( void ) {}
BitcoinExchange::BitcoinExchange( const BitcoinExchange & b ) { *this = b; }
BitcoinExchange &BitcoinExchange::operator=( const BitcoinExchange & b )
{
	(void) b;
	return (*this);
}

BitcoinExchange::~BitcoinExchange( void ) {}

// utils
	std::string	BitcoinExchange::_trim( std::string s )
	{
		return (s.substr (s.find_first_not_of (" "), 
			s.find_last_not_of (" ") + 1));
	}

// returns whether a date is valid or not
bool	BitcoinExchange::_isValidDate( const Date & d )
{
	if (d.getMonth () > 0 && d.getMonth () < 13
		&& d.getDay () > 0 &&
		(
			(d.getMonth () == 2 && d.getDay () < 29)
			|| ((d.getMonth () == 4 || d.getMonth () == 6 || d.getMonth () == 9 || d.getMonth () == 11)
				&& d.getDay () < 31)
			|| ((d.getMonth () == 1 || d.getMonth () == 3 || d.getMonth () == 5 
				|| d.getMonth () == 7 || d.getMonth () == 8 || d.getMonth () == 10
				|| d.getMonth () == 12) && d.getDay () < 32)
		))
		return (true);
	return (false);
}

// parse db to std::map
std::map<Date, double>  BitcoinExchange::_parse( std::string dbPathn )
{
	std::ifstream				s;
	std::map<Date, double>		map;
	std::string					ln;
	bool						isHeader;

	s.open (dbPathn);
	isHeader = true;
	while (std::getline (s, ln))
	{
		if (isHeader)
		{
			isHeader = false;
			continue ;
		}
		map.insert (std::make_pair (
			Date (_trim (ln.substr (0, ln.find (',')))), 
			std::stod (_trim (ln.substr (ln.find (',') + 1)))));
	}
	return (map);
}

int	BitcoinExchange::_putError ( std::string err )
{
	std::cerr << "\001\033[0;31m\002Error: " << err << "\001\033[0m\002" << std::endl;
	return (1);
}

// returns whether a str is empty or not
bool	BitcoinExchange::_isEmpty ( std::string s )
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\v'
			&& s[i] != '\n' && s[i] != '\r' && s[i] != '\f')
			return (false);
	return (true);
} 

// validates the spacing or the format of an input file's line
bool	BitcoinExchange::_hasValidSpacing ( std::string ln )
{
	int		i;
	bool	status;
	
	i = -1;
	status = false;
	while (ln[++i])
	{
		if (ln[i] == '\t' || ln[i] == '\v'
			|| ln[i] == '\n' || ln[i] == '\r' || ln[i] == '\f')
			return (!_putError ("only valid whitespace is space"));
		else if (ln[i] == ' ')
		{
			if (i == 0)
				return (!_putError ("invalid leading space"));
			else if (!status)
				status = true;
			else
				return (!_putError ("too many spaces"));
		}
		else if (ln[i] == '|')
		{
			if (!status)
				return (!_putError ("missing space"));
			else
				status = false;
			if (ln[i + 1] != ' ')
				return (!_putError ("missing space"));
		}
	}
	return (true);
}

//  converts and displays the values to bitcoin
int	BitcoinExchange::toBitcoin( std::string dbPathn, std::string amountsPathn )
{
	std::map<Date, double> 				db;
	std::ifstream						s;
	std::string							ln;
	std::string							dateStr;
	std::string							valStr;
	double								val;
	Date								date;
	std::map<Date, double>::iterator	it;
	std::map<Date, double>::iterator	it2;
	bool								isHeader;
	bool								bool_lower;
	
	s.open (dbPathn);
	if (!s.is_open ())
		return (_putError ("failed to open database"));
	s.close ();
	s.open (amountsPathn);
	if (!s.is_open ())
		return (_putError ("failed to open input file"));
	db = _parse (dbPathn);
	isHeader = true;
	while (std::getline (s, ln))
	{
		if (isHeader)
		{
			isHeader = false;
			continue ;
		}
		try
		{
			if (_hasValidSpacing (ln))
			{
				dateStr = ln.substr (0, ln.find ('|'));
				if (!_isEmpty (dateStr))
				{
					dateStr = _trim (dateStr);
					date = Date (dateStr);
					if (_isValidDate (date) && ln.find ('|') != std::string::npos)
					{
						valStr = ln.substr (ln.find ('|') + 1);
						if (!_isEmpty (valStr))
						{
							valStr = _trim (valStr);
							val = stod (valStr);
							if (val >= 0 && val <= 1000)
							{
								it = db.find (date);
								if (it != db.end ())
									std::cout << "\001\033[0;36m\002"
										<< date << " => " << val << " *" 
										<< it->second << " = " << val * it->second 
										<< " btc." << "\001\033[0m\002" << std::endl;
								else
								{
									bool_lower = false;
									it2 = db.begin ();
									it = db.end ();
									while (it2 != db.end ())
									{
										if (it2->first < date && (!bool_lower
											|| it2->first > it->first))
										{
											it = it2;
											if (!bool_lower)
												bool_lower = true;
										}
										it2++;
									}
									if (it != db.end ())
									{
										std::cout << "\001\033[0;33m\002Warning: using lower closest date for "
											<< date << " (" << it->first << ")" " => " << val << " *" 
											<< it->second << " = " << val * it->second 
											<< " btc." << "\001\033[0m\002" << std::endl;
									}
									else
										_putError ("no available exchange rate for this day => " + dateStr);
								}
							}
							else if (val < 0)
								_putError ("not a positive amount: " + valStr);
							else
								_putError ("too large a number: " + valStr);
						}
						else
							_putError ("value not found: \"" + ln + "\"");
					}
					else if (ln.find ('|') == std::string::npos)
						_putError ("seperator not found => \"" + ln + "\"");
					else
						_putError ("invalid date => " + dateStr);
				}
				else
					_putError ("date not found: \"" + ln + "\"");
			}
		}
		catch(const std::exception & e)
		{
			_putError (e.what ());
		}
	}
	return (0);
}
