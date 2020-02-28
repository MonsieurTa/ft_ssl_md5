/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:23:21 by wta               #+#    #+#             */
/*   Updated: 2020/02/28 18:32:55 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# define BASE64_OPT			0x1
# define DECRYPT_OPT		0x2
# define ENCRYPT_OPT		0x4
# define KEY_OPT			0x8
# define PASSWORD_OPT		0x10
# define SALT_OPT			0x20
# define INIT_VECTOR_OPT	0x80

# define SALT_SIZE			20

int		set_des_cbc(t_des *des_env, char *name);
t_hash	prf(char *key, char salt[SALT_SIZE]);


#endif
