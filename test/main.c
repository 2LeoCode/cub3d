double	decimalpart(double x)
{
	return (x - (int)x);
}

int		main(void)
{
	double x = 5.6;
	double dec = decimalpart(x);

	printf("%lf %lf", x, dec);
	return (0);
}