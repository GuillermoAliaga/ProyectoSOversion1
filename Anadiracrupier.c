#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	int ID_crup;
	float engano;
	float trampa;
	char ID_crups [2];
	char enganos [3];
	char trampas [3];
	int i;
	char consulta [80];
	//Creamos una conexion al servidor MYSQL
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexi\uffc3\uffb3n, entrando nuestras claves de acceso y
	//el nombre de la base de datos a la que queremos acceder
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "crupier",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//Introduciremos en la base de datos 4 personas,
	//cuyos datos pedimos al usuario
	for (i=0; i<1; i++) {
		printf ("Escribe el ID_crup, engano y  trampa, separados por un blanco\n");
		err = scanf ("%d %f %f", &ID_crup, &engano, &trampa);
		if (err!=3) {
			printf ("Error al introducir los datos \n");
			exit (1);
		}
		// Ahora construimos el string con el comando SQL
		// para insertar la persona en la base. Ese string es:
		// INSERT INTO personas VALUES ('dni', 'nombre', edad);
		strcpy (consulta, "INSERT INTO actcrupier VALUES (");
		//concatenamos el dni
		sprintf(ID_crups, "%d", ID_crup);
		strcat (consulta, ID_crups);
		strcat (consulta, ",");
		//concatenamos el nombre
		sprintf(enganos, "%f", engano);
		strcat (consulta, enganos);
		strcat (consulta, ",");
		//convertimos la edad en un string y lo concatenamos
		sprintf(trampas, "%f", trampa);
		strcat (consulta, trampas);
		strcat (consulta, ");");
		printf("consulta = %s\n", consulta);
		// Ahora ya podemos realizar la insercion
		err = mysql_query(conn, consulta);
		if (err!=0) {
			printf ("Error al introducir datos la base %u %s\n",
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
	}
	// cerrar la conexion con el servidor MYSQL
	mysql_close (conn);
	exit(0);
}
