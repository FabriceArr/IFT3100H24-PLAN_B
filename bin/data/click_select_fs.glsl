// implémentation de la technique vue ici https://ogldev.org/www/tutorial29/tutorial29.html with minor changes.

#version 330

uniform uint ObjectPointer; //since pointers are only integer pointing to where the object is store in memory, placing the pointer as the way to identify the opbject clicked will be very easy to track down 

out uvec3 fragment_couleur;

void main()
{
  fragment_couleur = uvec3(ObjectPointer, 0, 0);
}
