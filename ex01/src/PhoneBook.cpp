/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:14:53 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/09/04 17:36:51 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PhoneBook.hpp"

PhoneBook::PhoneBook(void)
{
	this->index = 0;
}

PhoneBook::~PhoneBook(void)
{
}

int PhoneBook::get_valid_index(std::string prompt)
{
	int	select_index;
	std::string input;
    
	while (1)
	{
		select_index = -1;
		input = get_input(prompt);
		select_index = std::atoi(input.c_str());
		if (input.length() == 1 && input[0] >= '0' && input[0] <= '7'
			&& this->contacts[select_index].get_first_name() != "")
			return (select_index);
		std::cout << RED << "Error!: Invalid index. Please try again." << ORIGINAL << std::endl;
	}
}
void PhoneBook::search_and_display_contact(void)
{
	int	select_index;
	std::string chosen_index;
    
	if (this->contacts[0].get_first_name() == "")
	{
		std::cout << RED << "     No contacts to display." << ORIGINAL << std::endl;
		return ;
	}
	select_index = -1;
	select_index = get_valid_index("Please enter the index of the contact you wish to view: ");
	std::cout << BLUE << "Contact details for index " << select_index << ":" << ORIGINAL << std::endl;
	this->contacts[select_index].display_contact();
}

void PhoneBook::display_contact_list(void)
{
	int	i;
	std::string first_name;
	std::string last_name;
	std::string nickname;
    
	std::cout << "     Index|First Name| Last Name|  Nickname" << std::endl;
	i = 0;
	while (i < 8 && this->contacts[i].get_first_name() != "")
	{
		std::cout << std::setw(10) << i << "|";
		first_name = this->contacts[i].get_first_name();
		last_name = this->contacts[i].get_last_name();
		nickname = this->contacts[i].get_nickname();
		if (first_name.length() > 10)
			first_name = first_name.substr(0, 9) + ".";
		if (last_name.length() > 10)
			last_name = last_name.substr(0, 9) + ".";
		if (nickname.length() > 10)
			nickname = nickname.substr(0, 9) + ".";
		std::cout << std::setw(10) << first_name << "|";
		std::cout << std::setw(10) << last_name << "|";
		std::cout << std::setw(10) << nickname << std::endl;
		i++;
	}
}

int PhoneBook::search_contact(void)
{
	display_contact_list();
	search_and_display_contact();
	return (0);
}

std::string PhoneBook::get_valid_phone_nbr(std::string prompt)
{
	std::string input;
	while (1)
	{
		input = get_input(prompt);
		if (str_is_valid_phone_nbr(input))
			return (input);
		std::cout << RED << "Error: Invalid phone number" << ORIGINAL << std::endl;
	}
}

std::string PhoneBook::get_valid_input(std::string prompt)
{
	std::string input;
	while (1)
	{
		input = get_input(prompt);
		if (!input.empty() && !str_is_only_whitespace(input))
			return (input);
		std::cout << RED << "Error: Invalid input" << ORIGINAL << std::endl;
	}
}
Contact PhoneBook::create_contact(void)
{
	Contact	newContact;

	std::cout << "Please enter the following information:" << std::endl;
	newContact.set_first_name(get_valid_input("First Name: "));
	newContact.set_last_name(get_valid_input("Last Name: "));
	newContact.set_nickname(get_valid_input("Nickname: "));
	newContact.set_phone_number(get_valid_phone_nbr("Phone Number: "));
	newContact.set_darkest_secret(get_valid_input("Darkest Secret: "));
	return (newContact);
}

void PhoneBook::add_contact(void)
{
	Contact	newContact;

	newContact = create_contact();
	if (this->index == 8)
		this->index = 0;
	this->contacts[this->index] = newContact;
	this->index++;
	std::cout << GREEN << "Contact added successfully!" << ORIGINAL << std::endl;
}
