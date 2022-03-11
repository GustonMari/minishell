#include "../includes/function.h"

/*Check dans str si avant le = il n'y a que des caracteres
alphanum, sinon on retourne 1 en affichant un message d'erreur*/

int	ft_check_export(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (!ft_isalnum(str[i]))
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			g_status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

/*Affiche une ligne de export en ajoutant des quotes pour
la valeur des variables d'env pour reproduire export.
(n'ajoute pas de quotes si la variable n'a pas de valeur)*/

void	ft_putstr_export_no_arg(char *str)
{
	int	i;
	int	first_equal;

	i = 0;
	first_equal = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		if((str[i] == '=') && first_equal == 0)
		{
			write(1, "\"", 1);
			first_equal = 1;
		}
		i++;
	}
	if (first_equal == 1)
		write(1, "\"", 1);
}

/*Affiche export quand on ne met aucun argument devant
(c'est l'environnement printe avec quelques modifs)*/

int		ft_print_export_no_arg(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_export_no_arg(env[i]);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}