/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:31:56 by tfarenga          #+#    #+#             */
/*   Updated: 2021/01/21 15:42:18 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

template <typename T>
struct Bit
{
    bool operator()(const T &left, const T &right) const
    {
        return left < right;
    }
};

template <typename T>
struct Peer
{
    bool operator()(const T &left, const T &right) const
    {
        return left == right;
    }
};

#endif