/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mime.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areheman <areheman@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:54:56 by areheman          #+#    #+#             */
/*   Updated: 2023/07/06 11:55:22 by areheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIME_HPP
#define MIME_HPP

#include "utiles.hpp"

class Mime
{
    public:
        Mime();
        std::string getMimeType(std::string extension);
    private:
        std::map<std::string, std::string> _mime_types;
        
};


#endif// MIME_HPP