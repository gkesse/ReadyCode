https://stackoverflow.com/questions/7299816/qradiobuttons-in-two-different-layouts
À partir de la documentation QRadioButton :

Si l''auto-exclusivité est activée, 
les boutons radio appartenant au même widget parent se comportent comme 
s'ils faisaient partie du même groupe de boutons exclusifs. 

Si vous avez besoin de plusieurs groupes de boutons exclusifs 
pour les boutons radio appartenant au même widget parent, 
placez-les dans un QButtonGroup .

(L'exclusivité automatique est activée par défaut.)

Vous devriez le faire 
(et continuer à ajouter l'individu QRadioButtons à votre mise en page).
