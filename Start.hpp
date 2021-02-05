/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Start.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:29:00 by tfarenga          #+#    #+#             */
/*   Updated: 2021/02/03 12:15:49 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef START_HPP
# define START_HPP

# include <cstddef>

namespace ft
{
	struct input_tag {};
	struct forward_tag: input_tag {};
	struct bidirectional_tag: forward_tag {};
	struct random_access: bidirectional_tag {};
};

#endif