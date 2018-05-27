/*
 * Copyright 2017 ClinRisk Ltd.
 *
 * This file is part of QDiabetes-2018 (https://qdiabetes.org).
 *
 * QDiabetes-2018 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QDiabetes-2018 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with QDiabetes-2018.  If not, see http://www.gnu.org/licenses/.
 *
 * Additional terms
 *
 * The following disclaimer must be held together with any risk score score generated by this code.
 * If the score is displayed, then this disclaimer must be displayed or otherwise be made easily accessible, e.g. by a prominent link alongside it.
 *   The initial version of this file, to be found at http://qdiabetes.org, faithfully implements QDiabetes-2018.
 *   ClinRisk Ltd. have released this code under the GNU Affero General Public License to enable others to implement the algorithm faithfully.
 *   However, the nature of the GNU Affero General Public License is such that we cannot prevent, for example, someone accidentally
 *   altering the coefficients, getting the inputs wrong, or just poor programming.
 *   ClinRisk Ltd. stress, therefore, that it is the responsibility of the end user to check that the source that they receive produces the same
 *   results as the original code found at http://qdiabetes.org.
 *   Inaccurate implementations of risk scores can lead to wrong patients being given the wrong treatment.
 *
 * End of additional terms
 *
 */

// Model A

static double type2_female_raw(
int age,int b_atypicalantipsy,int b_corticosteroids,int b_cvd,int b_gestdiab,int b_learning,int b_manicschiz,int b_pos,int b_statin,int b_treatedhyp,double bmi,int ethrisk,int fh_diab,int smoke_cat,int surv,double town
)
{
	surv = 10;
	double survivor[11] = {
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0.986227273941040
	};

	/* The conditional arrays */

	double Iethrisk[10] = {
		0,
		0,
		1.0695857881565456000000000,
		1.3430172097414006000000000,
		1.8029022579794518000000000,
		1.1274654517708020000000000,
		0.4214631490239910100000000,
		0.2850919645908353000000000,
		0.8815108797589199500000000,
		0.3660573343168487300000000
	};
	double Ismoke[5] = {
		0,
		0.0656016901750590550000000,
		0.2845098867369837400000000,
		0.3567664381700702000000000,
		0.5359517110678775300000000
	};

	/* Applying the fractional polynomial transforms */
	/* (which includes scaling)                      */

	double dage = age;
	dage=dage/10;
	double age_2 = pow(dage,3);
	double age_1 = pow(dage,.5);
	double dbmi = bmi;
	dbmi=dbmi/10;
	double bmi_1 = dbmi;
	double bmi_2 = pow(dbmi,3);

	/* Centring the continuous variables */

	age_1 = age_1 - 2.123332023620606;
	age_2 = age_2 - 91.644744873046875;
	bmi_1 = bmi_1 - 2.571253299713135;
	bmi_2 = bmi_2 - 16.999439239501953;
	town = town - 0.391116052865982;

	/* Start of Sum */
	double a=0;

	/* The conditional sums */

	a += Iethrisk[ethrisk];
	a += Ismoke[smoke_cat];

	/* Sum from continuous values */

	a += age_1 * 4.3400852699139278000000000;
	a += age_2 * -0.0048771702696158879000000;
	a += bmi_1 * 2.9320361259524925000000000;
	a += bmi_2 * -0.0474002058748434900000000;
	a += town * 0.0373405696180491510000000;

	/* Sum from boolean values */

	a += b_atypicalantipsy * 0.5526764611098438100000000;
	a += b_corticosteroids * 0.2679223368067459900000000;
	a += b_cvd * 0.1779722905458669100000000;
	a += b_gestdiab * 1.5248871531467574000000000;
	a += b_learning * 0.2783514358717271700000000;
	a += b_manicschiz * 0.2618085210917905900000000;
	a += b_pos * 0.3406173988206666100000000;
	a += b_statin * 0.6590728773280821700000000;
	a += b_treatedhyp * 0.4394758285813711900000000;
	a += fh_diab * 0.5313359456558733900000000;

	/* Sum from interaction terms */

	a += age_1 * b_atypicalantipsy * -0.8031518398316395100000000;
	a += age_1 * b_learning * -0.8641596002882057100000000;
	a += age_1 * b_statin * -1.9757776696583935000000000;
	a += age_1 * bmi_1 * 0.6553138757562945200000000;
	a += age_1 * bmi_2 * -0.0362096572016301770000000;
	a += age_1 * fh_diab * -0.2641171450558896200000000;
	a += age_2 * b_atypicalantipsy * 0.0004684041181021049800000;
	a += age_2 * b_learning * 0.0006724968808953360200000;
	a += age_2 * b_statin * 0.0023750534194347966000000;
	a += age_2 * bmi_1 * -0.0044719662445263054000000;
	a += age_2 * bmi_2 * 0.0001185479967753342000000;
	a += age_2 * fh_diab * 0.0004161025828904768300000;

	/* Calculate the score itself */
	double score = 100.0 * (1 - pow(survivor[surv], exp(a)) );
	return score;
}
