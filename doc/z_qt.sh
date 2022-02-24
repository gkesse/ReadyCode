#================================================
### qlineedit
#================================================

# inputMask
->	role
	-	masque de saisie de validation
->	retour
	-	si masque : masque
	-	si pas de masque : vide
->	annulation
	-	passer vide : ""
->	contenu
	-	caracteres masques
	-	meta-caracteres
	-	separateurs
->	caractere de masque
	-	A : lettre requise : AZ, az
	-	a : lettre autorisee mais non obligatoire : AZ, az
	-	N : lettre ou chiffre requis : AZ, az, 0-9
	-	n : lettre ou chiffre autorise mais non obligatoire : AZ, az, 0-9
	-	X : tout caractere non vide requis
	-	x : tout caractere non vide autorise mais non obligatoire
	-	9 : chiffre requis : 0-9
	-	0 : chiffre autorise mais non obligatoire
	-	D : nombre > 0 requis : 1-9
	-	d : nombre > 0 autorise mais non obligatoire : 1-9
	-	H : caractere hexadecimal requis : AF, 0-9
	-	h : caractere hexadecimal autorise mais non obligatoire : AF, 0-9
	-	B : caractere binaire requis : 0-1
	-	b : caractere binaire autorise mais non obligatoire : 0-1
->	meta-caracteres	
	
#================================================
### qobject
#================================================


















