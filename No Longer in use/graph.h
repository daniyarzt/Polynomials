void grothendieck_expansion1()
{
        //  checking fancy formula
    string lambda, theta;
    int n;
    //cin >> lambda >> theta >> n;
    lambda = "11", theta = "2", n = 5;

    assert(n >= (int)lambda.size() && n >= (int)theta.size());
    while((int)lambda.size() < n)
        lambda += '0';
    while((int)theta.size() < n)
        theta += '0';

    Polynomial leftSide = grassman(lambda, n);
    leftSide *= grassman(theta, n);

    Polynomial g31 = grassman("31", n);
    leftSide -= g31;

    Polynomial g311 = grassman("311", n);
    g311 *= Xpower(n + 1, 1);
    g311 *= Polynomial(-1);
    leftSide -= g311;

    Polynomial g211 = grassman("211", n);
    leftSide -= g211;

    Polynomial coef = Xpower(n + 1, 1);
    coef -= Xpower(n + 3, 1);
    coef *= Polynomial(-1);
    Polynomial g2111 = grassman("2111", n);
    g2111 *= coef;
    leftSide -= g2111;

    coef = Xpower(n + 1, 1);
    coef -= Xpower(n + 3, 1);
    coef *= Xpower(n + 1, 1);
    Polynomial g3111 = grassman("3111", n);
    g3111 *= coef;
    leftSide -= g3111;

    coef = Xpower(n + 1, 1);
    coef -= Xpower(n + 3, 1);
    Polynomial tmp = Xpower(n + 1, 1);
    tmp -= Xpower(n + 4, 1);
    coef *= tmp;
    Polynomial g21111 = grassman("21111", n);
    g21111 *= coef;
    leftSide -= g21111;

    coef = Xpower(n + 1, 1);
    coef -= Xpower(n + 3, 1);
    tmp = Xpower(n + 1, 1);
    tmp -= Xpower(n + 4, 1);
    coef *= tmp;
    coef *= Xpower(n + 1, 1);
    coef *= Polynomial(-1);
    Polynomial g31111 = grassman("31111", n);
    g31111 *= coef;
    leftSide -= g31111;

    leftSide.normalize();
    leftSide.print();


/*
    while(true)
    {
        system("cls");
        leftSide.print();
        string shape;
        cin >> shape;
        grassman(shape, n).print();
        system("pause");
    }
*/

}
