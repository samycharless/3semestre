#include <Windows.h>
#include <CommCtrl.h>
#include "Resource.h"
#include <string.h>
#include <fstream>
//#include<iostream>
//#include <iomanip>
#include <ctime>
#include <string>
#include <charconv>
//#include <sstream> 

using namespace std;

struct usuario {
	char nombre[100], contra[100], alias[100], nombrecomp[100];
	char direccion[100];
	char aux[3000];
	int val = 0;
	usuario* sig;
	usuario* ant;


}*origen, * anterior, * aux;

struct productos {
	char ID[20], cantinv[50], nomproducto[500], marca[500], descripcion[800], precio[50];
	char aux[3000];
	char direccion2[500], direccion3[500];
	productos* sig;
	productos* ant;
}*origenp, * anteriorp;

struct envios {
	char cant[50], total[50], calle[50], colonia[50], ciudad[50], mensaje[50], nproducto[100], estado[100];
	char aux[3000];
	SYSTEMTIME tiempo;
	envios* sig;
	envios* ant;
}*origene, * anteriore;

usuario* ingresar = new usuario();
productos* ingresarp = new productos();
productos* buscarp = origenp;
productos* auxp = origenp;
envios* buscare = origene;
envios* ingresare = new envios();
envios* actuale = (envios*)malloc(sizeof(envios));
int mess = 0, foto = 0, val = 0, n, y, a;
HBITMAP image, iproducto1, iproducto2;
char personabuscada[100];
char direccionaux[100], direccionaux2[100], direccionaux3[100];
char auxeliminare[500];
//char Day[32], year[32], month[32];
usuario* usuarioactual;
OPENFILENAME openfilename;
fstream myFile;
TCHAR buf[200];


HINSTANCE ventanas;


BOOL CBprimerventana(HWND, UINT, WPARAM, LPARAM);
BOOL CBregistrar(HWND, UINT, WPARAM, LPARAM);
BOOL CBproductos(HWND, UINT, WPARAM, LPARAM);
BOOL CBinfovendedor(HWND, UINT, WPARAM, LPARAM);
BOOL CBenvios(HWND, UINT, WPARAM, LPARAM);
BOOL CBaltaproductos(HWND, UINT, WPARAM, LPARAM);
BOOL CBaltaenvios(HWND, UINT, WPARAM, LPARAM);
BOOL CBmodificarinfo(HWND, UINT, WPARAM, LPARAM);
BOOL CBmodificarproducto(HWND, UINT, WPARAM, LPARAM);
BOOL CBmodificarenvios(HWND, UINT, WPARAM, LPARAM);
BOOL CBresumenenvios(HWND, UINT, WPARAM, LPARAM);
BOOL CBeliminarproductos(HWND, UINT, WPARAM, LPARAM);
BOOL CBeliminarenvios(HWND, UINT, WPARAM, LPARAM);
BOOL CBfiltrodeenvios(HWND, UINT, WPARAM, LPARAM);

int compararfechas(SYSTEMTIME fecha1, SYSTEMTIME fecha2) {
	//-1 fecha1 < fecha2
	// 0 fecha1 = fecha2
	// 1 fecha1 > fecha2

	if (fecha1.wYear < fecha2.wYear)
	{
		return -1;
	}

	if (fecha1.wYear > fecha2.wYear)
	{
		return 1;
	}
	// El a�o es el mismo
	if (fecha1.wMonth < fecha2.wMonth)
	{
		return -1;
	}

	if (fecha1.wMonth > fecha2.wMonth)
	{
		return 1;
	}
	//El a�o y el mes es el mismo
	if (fecha1.wDay < fecha2.wDay)
	{
		return -1;
	}

	if (fecha1.wDay > fecha2.wDay)
	{
		return 1;
	}
	//El a�o, mes y dia es el mismo
	return 0;
}

int validarCadenas(char cadena[100]);

void listaUsuario() {

	if (origen == NULL) {
		origen = ingresar;
		anterior = ingresar;
		origen->sig = NULL;
		origen->ant = NULL;
	}
	else
	{
		anterior->sig = ingresar;
		ingresar->ant = anterior;
		anterior = ingresar;
		ingresar->sig = NULL;
	}

}

void listaProductos() {

	if (origenp == NULL) {
		origenp = ingresarp;
		anteriorp = ingresarp;
		origenp->sig = NULL;
		origenp->ant = NULL;
	}
	else
	{
		anteriorp->sig = ingresarp;
		ingresarp->ant = anteriorp;
		anteriorp = ingresarp;
		ingresarp->sig = NULL;
	}
	ingresarp = new productos();
}

void listaEnvios() {

	if (origene == NULL) {
		origene = ingresare;
		anteriore = ingresare;
		origene->sig = NULL;
		origene->ant = NULL;
	}
	else
	{
		anteriore->sig = ingresare;
		ingresare->ant = anteriore;
		anteriore = ingresare;
		ingresare->sig = NULL;
	}
	ingresare = new envios();
}

void buscarppornombre(char nomproducto[500]) {
	int salir = 0;

	buscarp = origenp;
	do
	{
		if (strcmp(buscarp->nomproducto, nomproducto) == 0) {
			salir = 1;
		}
		else
		{
			buscarp = buscarp->sig;
		}

	} while (buscarp != NULL && salir == 0);

}

void buscarepornombre(char nomproducto[500]) {
	int salir = 0;

	buscare = origene;
	do
	{
		if (strcmp(buscare->nproducto, nomproducto) == 0) {
			salir = 1;
		}
		else
		{
			buscare = buscare->sig;
		}

	} while (buscare != NULL && salir == 0);

}

void guardarus() {
	
	aux = origen;
	fstream gusuarios;
	gusuarios.open("ListaUsuarios.bin", ios::binary | ios::trunc | ios::out);
	if (gusuarios.is_open())
	{
		while (aux != NULL)
		{
			gusuarios.write(reinterpret_cast<char*>(aux), sizeof(usuario));
			aux = aux->sig;
		}
		gusuarios.close();
		return;
	}

	return;
}
/*
void cargarus() {
	aux = origen;
	fstream cusuarios;
	cusuarios.open("ListaUsuarios.png", ios::binary | ios::in | ios::ate);
	if (cusuarios.is_open()) {
		int size = cusuarios.tellg();
		cusuarios.seekg(0); // irme al principio del archivo

		for (int i = 0; i < size / sizeof(usuario); i++)
		{
			usuario* temp = new usuario;
			cusuarios.read(reinterpret_cast<char*>(temp), sizeof(usuario));
			aux->nombre = temp->nombre; contra[100], alias[100], nombrecomp[100];
			char direccion[100];
			char aux[3000];
			int val = 0;
			usuario* sig;
			usuario* ant;
			cout<<temp->nombre;
			cusuarios.seekg(i+1 * sizeof(usuario));
			delete reinterpret_cast<char*>(temp);


			if (origen == NULL)
			{
				origen = new usuario;
				usuario* temp = new usuario;
				cusuarios.seekg(0);
				cusuarios.read(reinterpret_cast<char*>(temp), sizeof(usuario));
				origen->nombre = temp->nombre;
				origen->contra = temp->contra;
				origen->precio = temp->precio;
				origen->ant = NULL;
				origen->sig = NULL;
				delete reinterpret_cast<char*>(temp);
				continue;
			}
			aux = origen;
			while (aux->sig != NULL)
				aux = aux->sig;
			aux->sig = new usuario;
			usuario* temp = new usuario;
			cusuarios.seekg(i * sizeof(usuario));
			cusuarios.read(reinterpret_cast<char*>(temp), sizeof(usuario));
			aux->sig->ant = aux;
			aux->sig->sig = NULL;
			aux = aux->sig;
			aux->ID = temp->ID;
			aux->nombre = temp->nombre;
			aux->precio = temp->precio;
			idActual = aux->ID;
			delete reinterpret_cast<char*>(temp);
		}
		cusuarios.close();
		cout << "Carga exitosa" << endl;
		return;
	}
	cout << "No se pudo cargar" << endl;
	return;
}*/


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmd, int modo) {
	DialogBox(ventanas, MAKEINTRESOURCE(IDD_INGRESA), NULL, (DLGPROC)CBprimerventana);

	return 0;
}

//primer ventana
BOOL CBprimerventana(HWND handler, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_COMMAND: {
		int picar = LOWORD(wParam);
		switch (picar) {

		case IDC_BUTTON3:
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_REGISTRAR), NULL, (DLGPROC)CBregistrar);
			break;


		case IDC_BUTTON4:
			char insesion[100];
			char incontra[100];
			usuario* buscar = new usuario;
			SendDlgItemMessage(handler, IDC_EDIT1, WM_GETTEXT, sizeof(insesion), (LPARAM)insesion);
			int salir = 0;
			buscar = origen;

			if (origen != NULL)
			{
				do
				{
					if (strcmp(buscar->nombre, insesion) == 0) {
						SendDlgItemMessage(handler, IDC_EDIT2, WM_GETTEXT, sizeof(incontra), (LPARAM)incontra);
						if (strcmp(buscar->contra, incontra) == 0)
						{
							EndDialog(handler, 0);
							DialogBox(ventanas, MAKEINTRESOURCE(IDD_ENVIO), NULL, (DLGPROC)CBenvios);
						}
						else
						{
							MessageBox(handler, "Contrase�a incorrecta", "Error ", MB_OK);// se cicla
						}
						salir = 1;
					}
					buscar = buscar->sig;
				} while (buscar != NULL && salir == 0);
				if (salir == 0)
				{
					MessageBox(handler, "Usuario no encontrado", "Error ", MB_OK); // se traba
				}


			}
			else
			{
				MessageBox(handler, "Aun no te haz registrado", "Error ", MB_OK);// si sirve
			}


			break;
		}

		break;
	}


	}
	return 0;
}

//USUARIO
// ventana registrar
BOOL CBregistrar(HWND handler, UINT message, WPARAM wParam, LPARAM lParam) {


	switch (message) {
	case WM_COMMAND: {
		int picar = LOWORD(wParam);
		switch (picar) {

		case ID_OKR:

			char cadenaaux[100];
			SendDlgItemMessage(handler, IDC_EDIT1, WM_GETTEXT, sizeof(cadenaaux), (LPARAM)cadenaaux);

			if (validarCadenas(cadenaaux) == 0)
			{

				SendDlgItemMessage(handler, IDC_EDIT1, WM_GETTEXT, sizeof(ingresar->nombre), (LPARAM)ingresar->nombre);
				SendDlgItemMessage(handler, IDC_EDIT2, WM_GETTEXT, sizeof(ingresar->contra), (LPARAM)ingresar->contra);
				int yes = 0;
				int a = strlen(ingresar->contra);
				for (int i = 0; i < a; i++) {
					if (ingresar->contra[i] != '\0') {
						yes = 1;
					}
					else {
						MessageBox(handler, "Ingresa la contrase�a", "Error", MB_ICONERROR);
						yes = 0;
					}
				}
				if (yes == 1)
				{
					char insesion[100];
					usuario* buscar = new usuario;
					SendDlgItemMessage(handler, IDC_EDIT1, WM_GETTEXT, sizeof(insesion), (LPARAM)insesion);
					int salir = 0;
					buscar = origen;

					if (origen != NULL)
					{
						do
						{
							if (strcmp(buscar->nombre, insesion) == 0) {
								if ((MessageBox(handler, "Este nombre de usuario ya existe", "Error ", MB_OK)) == IDOK)
								{
									SendDlgItemMessage(handler, IDC_EDIT1, WM_SETTEXT, sizeof(""), (LPARAM)"");
									SendDlgItemMessage(handler, IDC_EDIT2, WM_SETTEXT, sizeof(""), (LPARAM)"");
								}
								salir = 1;
							}
							buscar = buscar->sig;

						} while (buscar != NULL && salir == 0);



					}
					listaUsuario();
					//guardarus();
					EndDialog(handler, 0);
					DialogBox(ventanas, MAKEINTRESOURCE(IDD_INFO), NULL, (DLGPROC)CBinfovendedor);

				}
				else
				{
					MessageBox(handler, "Ingresa todos los datos", "Error", MB_ICONERROR);
				}

			}
			else
			{
				MessageBox(handler, "Usa solo letras", "Error", MB_ICONERROR);
			}

		case IDCANCEL:
			EndDialog(handler, 0);
			break;
		}
		break;
	}
	}
	return false;
}
// ventana informacion del vendedor
BOOL CBinfovendedor(HWND handler, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {
	case WM_COMMAND: {
		int picar = LOWORD(wParam);
		char nomcompaux[100];
		switch (picar) {

		case IDC_Imagen:

			ZeroMemory(&openfilename, sizeof(openfilename));
			openfilename.lStructSize = sizeof(openfilename);
			openfilename.hwndOwner = handler;
			openfilename.lpstrFile = ingresar->direccion;
			openfilename.lpstrFile[0] = NULL;
			openfilename.nMaxFile = sizeof(ingresar->direccion);
			openfilename.lpstrFilter = "BMP\0*.BMP\0";
			openfilename.nFilterIndex = 0;
			openfilename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileName(&openfilename) == TRUE) {
				image = (HBITMAP)LoadImage(NULL, ingresar->direccion, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
				SendMessage(GetDlgItem(handler, IDC_FOTODEVENDEDOR), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
				int foto = 1;
			}



			break;

		case IDOKINFO:

			SendDlgItemMessage(handler, IDC_nomcomp, WM_GETTEXT, sizeof(nomcompaux), (LPARAM)nomcompaux);

			if (validarCadenas(nomcompaux) == 0) {

				SendDlgItemMessage(handler, IDC_nomcomp, WM_GETTEXT, sizeof(ingresar->nombrecomp), (LPARAM)ingresar->nombrecomp);
				SendDlgItemMessage(handler, IDC_alias, WM_GETTEXT, sizeof(ingresar->alias), (LPARAM)ingresar->alias);
				int yes = 0;
				int a = strlen(ingresar->alias);
				for (int i = 0; i < a; i++) {
					if (ingresar->alias[i] != '\0') {
						yes = 1;
					}
					else {
						MessageBox(handler, "Ingresa el alias de la empresa", "Error", MB_ICONERROR);
						yes = 0;
					}
				}
				if (yes == 1 && ingresar->direccion[0] != '\0') {

					listaUsuario();
					void guardarus();
					EndDialog(handler, 0);
					DialogBox(ventanas, MAKEINTRESOURCE(IDD_PRODUCTOS), NULL, (DLGPROC)CBproductos);


				}
				else
				{
					MessageBox(handler, "Ingresa todos los datos", "Error", MB_ICONERROR);
				}


			}
			else
			{
				MessageBox(handler, "Usa solo letras", "Error", MB_ICONERROR);
			}

			break;

		case IDCANCEL2:
			EndDialog(handler, 0);
			break;
		}
		break;
	}
	}
	return false;
}
// modificar informacion del vendedor
BOOL CBmodificarinfo(HWND handler, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

	case WM_INITDIALOG: {


		SendDlgItemMessage(handler, IDC_modnomcomp, WM_SETTEXT, sizeof(ingresar->nombrecomp), (LPARAM)ingresar->nombrecomp);
		SendDlgItemMessage(handler, IDC_modalias, WM_SETTEXT, sizeof(ingresar->alias), (LPARAM)ingresar->alias);
		image = (HBITMAP)LoadImage(NULL, ingresar->direccion, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
		SendMessage(GetDlgItem(handler, IDC_fotomodvendedor), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);


		break;
	}

	case WM_COMMAND: {
		int picar = LOWORD(wParam);
		//char nomcompaux[100];

		switch (picar) {

		case IDC_cambiarimagen:

			ZeroMemory(&openfilename, sizeof(openfilename));
			openfilename.lStructSize = sizeof(openfilename);
			openfilename.hwndOwner = handler;
			openfilename.lpstrFile = direccionaux;
			openfilename.lpstrFile[0] = NULL;
			openfilename.nMaxFile = sizeof(direccionaux);
			openfilename.lpstrFilter = "BMP\0*.BMP\0";
			openfilename.nFilterIndex = 0;
			openfilename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileName(&openfilename) == TRUE) {
				image = (HBITMAP)LoadImage(NULL, direccionaux, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
				SendMessage(GetDlgItem(handler, IDC_fotomodvendedor), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);

			}



			break;


		case IDOKmod:

			mess = MessageBox(handler, "Desea guardar los cambios?", "Aviso", MB_YESNO);
			if (mess == IDNO) {
				EndDialog(handler, 0);
			}
			else
			{
				strcpy_s(ingresar->direccion, direccionaux);
				SendDlgItemMessage(handler, IDC_modnomcomp, WM_GETTEXT, sizeof(ingresar->nombrecomp), (LPARAM)ingresar->nombrecomp);
				SendDlgItemMessage(handler, IDC_modalias, WM_GETTEXT, sizeof(ingresar->alias), (LPARAM)ingresar->alias);
				DialogBox(ventanas, MAKEINTRESOURCE(IDD_PRODUCTOS), NULL, (DLGPROC)CBproductos);
				EndDialog(handler, 0);

			}
			break;
		case IDCANCEL3:
			EndDialog(handler, 0);
			break;
		}
		break;
	}

	}
	return 0;
}


//PRODUCTOS
//ventana de productos
BOOL CBproductos(HWND handler, UINT message, WPARAM wParam, LPARAM lParam) {
	productos* actual = (productos*)malloc(sizeof(productos));

	switch (message) {

	case WM_INITDIALOG: {
		actual = origenp;

		SendDlgItemMessage(handler, IDC_mostrarnombrep, WM_SETTEXT, sizeof(ingresar->nombrecomp), (LPARAM)ingresar->nombrecomp);
		image = (HBITMAP)LoadImage(NULL, ingresar->direccion, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
		SendMessage(GetDlgItem(handler, IDC_mostrarfotop), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);

		if (origenp != NULL) {

			do {
				strcpy_s(actual->aux, "Nombre del producto:");
				strcat_s(actual->aux, actual->nomproducto);
				strcat_s(actual->aux, " || Cantidad en inventario:");
				strcat_s(actual->aux, actual->cantinv);
				strcat_s(actual->aux, " || Codigo:");
				strcat_s(actual->aux, actual->ID);
				strcat_s(actual->aux, " || Marca:");
				strcat_s(actual->aux, actual->marca);


				SendDlgItemMessage(handler, IDC_LISTAPRODUCTOS, LB_ADDSTRING, sizeof(actual->aux), (LPARAM)actual->aux);

				actual = actual->sig;

			} while (actual != NULL);
		}
		else
		{
			SendDlgItemMessage(handler, IDC_LISTAPRODUCTOS, LB_ADDSTRING, sizeof("NO HAY PRODUCTOS"), (LPARAM)"NO HAY PRODUCTOS");
		}
		break;
	}
	case WM_COMMAND: {

		int picar = LOWORD(wParam);
		switch (picar) {

		case IDC_BUTTON1:

			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_ALTAPRODUCTOS), NULL, (DLGPROC)CBaltaproductos);
			break;

		case IDC_modificarproducto:

			if (origenp == NULL)
			{
				MessageBox(handler, "No hay productos para modificar", "Error", MB_ICONERROR);
			}
			else
			{
				EndDialog(handler, 0);
				DialogBox(ventanas, MAKEINTRESOURCE(IDD_editarproductos), NULL, (DLGPROC)CBmodificarproducto);

			}
			break;

		case IDC_eliminarp: {
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_ELIMINARPRODUCTO), NULL, (DLGPROC)CBeliminarproductos);

			break;
		}

		case ID_VENDEDORES_MODIFICARINFORMACION:
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_modus), NULL, (DLGPROC)CBmodificarinfo);
			break;

		case MENUPRODUCTOS:
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_PRODUCTOS), NULL, (DLGPROC)CBproductos);

			break;

		case ID_MENUENVIOS:

			if (origenp == NULL)
			{
				MessageBox(handler, "No hay productos para enviar", "Error", MB_ICONERROR);
			}
			else
			{
				EndDialog(handler, 0);
				DialogBox(ventanas, MAKEINTRESOURCE(IDD_ENVIO), NULL, (DLGPROC)CBenvios);
				break;

			}


		case IDSALIR:
			mess = MessageBox(handler, "Estas seguro que quieres salir?", "Confirmacion salir", MB_YESNO);
			if (mess == IDYES) {
				PostQuitMessage(0);
			}
			break;

		}
	}
	}
	return false;

}
//ventas alta de productos
BOOL CBaltaproductos(HWND handler, UINT message, WPARAM wParam, LPARAM lParam) {
	productos* buscar = new productos;
	int salir = 0;
	buscar = origenp;

	switch (message) {
	case WM_INITDIALOG: {

		SendDlgItemMessage(handler, IDC_NOMBREVENDEDORP, WM_SETTEXT, sizeof(ingresar->nombrecomp), (LPARAM)ingresar->nombrecomp);
		image = (HBITMAP)LoadImage(NULL, ingresar->direccion, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
		SendMessage(GetDlgItem(handler, IDC_FOTOVENDEDORP), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);

		break;
	}

	case WM_COMMAND: {
		int picar = LOWORD(wParam);
		switch (picar) {

		case IDC_IMGP1:
			ZeroMemory(&openfilename, sizeof(openfilename));
			openfilename.lStructSize = sizeof(openfilename);
			openfilename.hwndOwner = handler;
			openfilename.lpstrFile = ingresarp->direccion2;
			openfilename.lpstrFile[0] = NULL;
			openfilename.nMaxFile = sizeof(ingresarp->direccion2);
			openfilename.lpstrFilter = "BMP\0*.BMP\0";
			openfilename.nFilterIndex = 0;
			openfilename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileName(&openfilename) == TRUE) {
				iproducto1 = (HBITMAP)LoadImage(NULL, ingresarp->direccion2, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
				SendMessage(GetDlgItem(handler, IDC_FOTOP1), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)iproducto1);

			}

			break;

		case IDC_IMGP2:

			ZeroMemory(&openfilename, sizeof(openfilename));
			openfilename.lStructSize = sizeof(openfilename);
			openfilename.hwndOwner = handler;
			openfilename.lpstrFile = ingresarp->direccion3;
			openfilename.lpstrFile[0] = NULL;
			openfilename.nMaxFile = sizeof(ingresarp->direccion3);
			openfilename.lpstrFilter = "BMP\0*.BMP\0";
			openfilename.nFilterIndex = 0;
			openfilename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileName(&openfilename) == TRUE) {
				iproducto2 = (HBITMAP)LoadImage(NULL, ingresarp->direccion3, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
				SendMessage(GetDlgItem(handler, IDC_FOTOP2), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)iproducto2);

			}

		default:
			break;

		case IDOK: {
			char productoaux[100], IDaux[100];

			SendDlgItemMessage(handler, IDC_nomproducto2, WM_GETTEXT, sizeof(ingresarp->nomproducto), (LPARAM)ingresarp->nomproducto);
			SendDlgItemMessage(handler, IDC_codigo, WM_GETTEXT, sizeof(ingresarp->ID), (LPARAM)ingresarp->ID);
			SendDlgItemMessage(handler, IDC_marca, WM_GETTEXT, sizeof(ingresarp->marca), (LPARAM)ingresarp->marca);
			SendDlgItemMessage(handler, IDC_descripcion, WM_GETTEXT, sizeof(ingresarp->descripcion), (LPARAM)ingresarp->descripcion);
			SendDlgItemMessage(handler, IDC_cantidad, WM_GETTEXT, sizeof(ingresarp->cantinv), (LPARAM)ingresarp->cantinv);
			SendDlgItemMessage(handler, IDC_preciop, WM_GETTEXT, sizeof(ingresarp->precio), (LPARAM)ingresarp->precio);
			if ((ingresarp->nomproducto[0] == '\0') || (ingresarp->ID[0] == '\0') || (ingresarp->marca[0] == '\0') || (ingresarp->precio[0] == '\0') ||
				(ingresarp->descripcion[0] == '\0') || (ingresarp->cantinv[0] == '\0') || (ingresarp->direccion2[0] == '\0') || (ingresarp->direccion3[0] == '\0'))
			{
				MessageBox(handler, "Ingresa todos los datos", "Error", MB_ICONERROR);
			}
			else
			{
				if (origenp != NULL)
				{
					do
					{
						if (strcmp(buscar->nomproducto, ingresarp->nomproducto) == 0) {
							(MessageBox(handler, "Este nombre de producto ya existe", "Error ", MB_OK));
							SendDlgItemMessage(handler, IDC_nomproducto2, WM_SETTEXT, sizeof(""), (LPARAM)"");
							salir = 1;
						}
						else
						{
							if (strcmp(buscar->ID, ingresarp->ID) == 0) {

								(MessageBox(handler, "Este codigo de producto ya existe", "Error ", MB_OK));
								SendDlgItemMessage(handler, IDC_codigo, WM_SETTEXT, sizeof(""), (LPARAM)"");
								salir = 1;
							}

						}
						buscar = buscar->sig;

					} while (buscar != NULL && salir == 0);



				}
				if (salir == 0)
				{

					listaProductos();
					EndDialog(handler, 0);
					DialogBox(ventanas, MAKEINTRESOURCE(IDD_PRODUCTOS), NULL, (DLGPROC)CBproductos);


				}
			}


			break;
		}

		case IDCANCEL4: {
			EndDialog(handler, 0);
			break;


		}

		case ID_VENDEDORES_MODIFICARINFORMACION: {
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_INFO), NULL, (DLGPROC)CBmodificarinfo);
			break;

		}
		case MENUPRODUCTOS: {
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_PRODUCTOS), NULL, (DLGPROC)CBproductos);
			break;
		}

		case ID_MENUENVIOS: {
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_ENVIO), NULL, (DLGPROC)CBenvios);
			break;

		}

		case IDSALIR: {

			mess = MessageBox(handler, "Estas seguro que quieres salir?", "Confirmacion salir", MB_YESNO);
			if (mess == IDYES) {
				PostQuitMessage(0);
			}
			break;
		}

		}
	}

	}
	return false;
}
// ventana modificar productos
BOOL CBmodificarproducto(HWND handler, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_INITDIALOG: {
		int i = 0;
		productos* buscarp = origenp;

		do
		{
			SendMessage(GetDlgItem(handler, IDC_modnomprod), CB_ADDSTRING, i, (LPARAM)buscarp->nomproducto);
			i++;
			buscarp = buscarp->sig;

		} while (buscarp != NULL);

		SendDlgItemMessage(handler, IDC_NOMBREVENDEDOR, WM_SETTEXT, sizeof(ingresar->nombrecomp), (LPARAM)ingresar->nombrecomp);
		image = (HBITMAP)LoadImage(NULL, ingresar->direccion, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
		SendMessage(GetDlgItem(handler, IDC_FOTOVENDEDOR), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
		break;
	}


	case WM_COMMAND: {

		int picar = LOWORD(wParam);
		switch (picar) {
		case IDC_cambiarimgp1: {

			ZeroMemory(&openfilename, sizeof(openfilename));
			openfilename.lStructSize = sizeof(openfilename);
			openfilename.hwndOwner = handler;
			openfilename.lpstrFile = direccionaux2;
			openfilename.lpstrFile[0] = NULL;
			openfilename.nMaxFile = sizeof(direccionaux2);
			openfilename.lpstrFilter = "BMP\0*.BMP\0";
			openfilename.nFilterIndex = 0;
			openfilename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileName(&openfilename) == TRUE) {
				image = (HBITMAP)LoadImage(NULL, direccionaux2, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
				SendMessage(GetDlgItem(handler, IDC_fotomodvendedor), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);

			}

			break;
		}

		case IDC_cambiarimgp2: {

			ZeroMemory(&openfilename, sizeof(openfilename));
			openfilename.lStructSize = sizeof(openfilename);
			openfilename.hwndOwner = handler;
			openfilename.lpstrFile = direccionaux3;
			openfilename.lpstrFile[0] = NULL;
			openfilename.nMaxFile = sizeof(direccionaux3);
			openfilename.lpstrFilter = "BMP\0*.BMP\0";
			openfilename.nFilterIndex = 0;
			openfilename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileName(&openfilename) == TRUE) {
				image = (HBITMAP)LoadImage(NULL, direccionaux3, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
				SendMessage(GetDlgItem(handler, IDC_fotomodvendedor), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);

			}

			break;
		}

		case IDOKmodp: {
			//productos* buscarp = origenp;

			mess = MessageBox(handler, "Desea guardar los cambios?", "Aviso", MB_YESNO);
			if (mess == IDNO) {
				EndDialog(handler, 0);
			}
			else
			{
				strcpy_s(ingresarp->direccion2, direccionaux2);
				strcpy_s(ingresarp->direccion3, direccionaux3);
				SendDlgItemMessage(handler, IDC_nuevonombreproducto, WM_GETTEXT, sizeof(buscarp->nomproducto), (LPARAM)buscarp->nomproducto);
				SendDlgItemMessage(handler, IDC_modcodigo, WM_GETTEXT, sizeof(buscarp->ID), (LPARAM)buscarp->ID);
				SendDlgItemMessage(handler, IDC_modcantinv, WM_GETTEXT, sizeof(buscarp->cantinv), (LPARAM)buscarp->cantinv);
				SendDlgItemMessage(handler, IDC_moddesc, WM_GETTEXT, sizeof(buscarp->descripcion), (LPARAM)buscarp->descripcion);
				SendDlgItemMessage(handler, IDC_modmarca, WM_GETTEXT, sizeof(buscarp->marca), (LPARAM)buscarp->marca);
				EndDialog(handler, 0);
				DialogBox(ventanas, MAKEINTRESOURCE(IDD_PRODUCTOS), NULL, (DLGPROC)CBproductos);

			}

			break;
		}


		case IDCANCEL5:
			EndDialog(handler, 0);
			break;

		case IDC_buscar:
			char productonom[100];
			SendDlgItemMessage(handler, IDC_modnomprod, WM_GETTEXT, sizeof(productonom), (LPARAM)productonom);
			buscarppornombre(productonom);
			SendDlgItemMessage(handler, IDC_nuevonombreproducto, WM_SETTEXT, sizeof(buscarp->nomproducto), (LPARAM)buscarp->nomproducto);
			SendDlgItemMessage(handler, IDC_modcodigo, WM_SETTEXT, sizeof(buscarp->ID), (LPARAM)buscarp->ID);
			SendDlgItemMessage(handler, IDC_modcantinv, WM_SETTEXT, sizeof(buscarp->cantinv), (LPARAM)buscarp->cantinv);
			SendDlgItemMessage(handler, IDC_moddesc, WM_SETTEXT, sizeof(buscarp->descripcion), (LPARAM)buscarp->descripcion);
			SendDlgItemMessage(handler, IDC_modmarca, WM_SETTEXT, sizeof(buscarp->marca), (LPARAM)buscarp->marca);
			image = (HBITMAP)LoadImage(NULL, buscarp->direccion2, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
			SendMessage(GetDlgItem(handler, IDC_STATIC1), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
			image = (HBITMAP)LoadImage(NULL, buscarp->direccion3, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
			SendMessage(GetDlgItem(handler, IDC_STATIC2), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);


			break;

			//break;
		}
	}
	}
	return false;
}
// ventana elimar p
BOOL CBeliminarproductos(HWND handler, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_INITDIALOG: {

		SendDlgItemMessage(handler, IDC_NOMBREVENDEDORPELIMINAR, WM_SETTEXT, sizeof(ingresar->nombrecomp), (LPARAM)ingresar->nombrecomp);
		image = (HBITMAP)LoadImage(NULL, ingresar->direccion, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
		SendMessage(GetDlgItem(handler, IDC_FOTOVENDEDORPELIMINAR), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
		int i = 0;
		productos* buscarp = origenp;

		do
		{
			SendMessage(GetDlgItem(handler, IDC_nombrepeliminar), CB_ADDSTRING, i, (LPARAM)buscarp->nomproducto);
			i++;
			buscarp = buscarp->sig;

		} while (buscarp != NULL);


		break;
	}
	case WM_COMMAND: {
		int picar = LOWORD(wParam);
		switch (picar) {
			case IDELIMINARPRODUCTO: {
						
					mess = MessageBox(handler, "Estas seguro que quieres eliminar este producto? Ya no podras recuperarlo", "Aviso", MB_YESNO);
					if (mess == IDNO) {
						PostQuitMessage(0);
					}
					else
					{

						if (buscarp->ant == NULL && buscarp->sig == NULL) //Unico NODO
						{
							delete buscarp;
							buscarp = origenp = NULL;
						}
						else if (buscarp->ant == NULL) //Primer Nodo
						{
							origenp = buscarp->sig;
							delete buscarp;
							origenp->ant = NULL;
							buscarp = origenp;
						}
						else if (buscarp->sig == NULL) //Ultimo Nodo
						{
							buscarp->ant->sig = NULL;
							delete buscarp;
							buscarp = origenp;
						}
						else //Nodo de enmedio
						{
							buscarp->ant->sig = buscarp->sig;
							buscarp->sig->ant = buscarp->ant;
							delete buscarp;
							buscarp = origenp;
						}
						
						EndDialog(handler, 0);
						DialogBox(ventanas, MAKEINTRESOURCE(IDD_PRODUCTOS), NULL, (DLGPROC)CBproductos);


					}
					


				

				break;
			}
			case IDC_buscareliminarp: {
				char eliminarauxnom[100];
				SendDlgItemMessage(handler, IDC_nombrepeliminar, WM_GETTEXT, sizeof(eliminarauxnom), (LPARAM)eliminarauxnom);
				buscarppornombre(eliminarauxnom);
				SendDlgItemMessage(handler, IDC_eliminarcodigop, WM_SETTEXT, sizeof(buscarp->ID), (LPARAM)buscarp->ID);
				SendDlgItemMessage(handler, IDC_elimiarcantidadp, WM_SETTEXT, sizeof(buscarp->cantinv), (LPARAM)buscarp->cantinv);
				SendDlgItemMessage(handler, IDC_eliminardescripcionp, WM_SETTEXT, sizeof(buscarp->descripcion), (LPARAM)buscarp->descripcion);
				SendDlgItemMessage(handler, IDC_eliminarmarcap, WM_SETTEXT, sizeof(buscarp->marca), (LPARAM)buscarp->marca);
				image = (HBITMAP)LoadImage(NULL, buscarp->direccion2, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
				SendMessage(GetDlgItem(handler, IDC_FOTOP1), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
				image = (HBITMAP)LoadImage(NULL, buscarp->direccion3, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
				SendMessage(GetDlgItem(handler, IDC_FOTOP2), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);

				break;
			}
			case IDCANCEL: {
				EndDialog(handler, 0);
				DialogBox(ventanas, MAKEINTRESOURCE(IDD_PRODUCTOS), NULL, (DLGPROC)CBproductos);

				break;
			}

				break;
		}
	}
				   break;
	}



	return 0;
}

//ENVIOS
// ventana de envios
BOOL CBenvios(HWND handler, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

	case WM_INITDIALOG: {
		actuale = origene;

		SendDlgItemMessage(handler, IDC_NOMBREVENDEDOREE, WM_SETTEXT, sizeof(ingresar->nombrecomp), (LPARAM)ingresar->nombrecomp);
		image = (HBITMAP)LoadImage(NULL, ingresar->direccion, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
		SendMessage(GetDlgItem(handler, IDC_FOTOVENDEDOREE), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);

		if (origene != NULL) {

			do {

				GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &actuale->tiempo, NULL, buf, 200);
				strcpy_s(actuale->aux, "Producto:");
				strcat_s(actuale->aux, actuale->nproducto);
				strcat_s(actuale->aux, " || Cantidad:");
				strcat_s(actuale->aux, actuale->cant);
				strcat_s(actuale->aux, " || Precio: $");
				strcat_s(actuale->aux, actuale->total);
				strcat_s(actuale->aux, " || Fecha de envio:");
				strcat_s(actuale->aux, buf);


				SendDlgItemMessage(handler, IDC_LIST2, LB_ADDSTRING, sizeof(actuale->aux), (LPARAM)actuale->aux);

				actuale = actuale->sig;

			} while (actuale != NULL);
		}
		else
		{
			SendDlgItemMessage(handler, IDC_LIST2, LB_ADDSTRING, sizeof("NO HAY ENVIOS"), (LPARAM)"NO HAY ENVIOS");
		}
		break;
	}

	case WM_COMMAND: {
		int picar = LOWORD(wParam);
		switch (picar) {

		case IDC_ALTAENVIOS:
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_ALTAENVIOS), NULL, (DLGPROC)CBaltaenvios);
			break;

		case IDC_BUTTON7:
			if (origene == NULL) {
				MessageBox(handler, "No hay envios aun", "Error", MB_ICONERROR);
			}
			else
			{

				EndDialog(handler, 0);
				DialogBox(ventanas, MAKEINTRESOURCE(IDD_resumenenvio), NULL, (DLGPROC)CBresumenenvios);
				break;
			}

			break;
		case IDC_modificare:
			if (origene == NULL) {
				MessageBox(handler, "No hay envios aun", "Error", MB_ICONERROR);
			}
			else
			{
				EndDialog(handler, 0);
				DialogBox(ventanas, MAKEINTRESOURCE(IDD_MODENVIOS), NULL, (DLGPROC)CBmodificarenvios);
				break;

			}
		case IDC_BUTTON2: {
			if (origene == NULL) {
				MessageBox(handler, "No hay envios aun", "Error", MB_ICONERROR);
			}
			else
			{
				EndDialog(handler, 0);
				DialogBox(ventanas, MAKEINTRESOURCE(IDD_ELIMINARENVIOS), NULL, (DLGPROC)CBeliminarenvios);
				break;
			}
		}
		case IDC_filtro: {
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_filtroenvios), NULL, (DLGPROC)CBfiltrodeenvios);
			break;
			break;
		}
		case ID_VENDEDORES_MODIFICARINFORMACION:
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_INFO), NULL, (DLGPROC)CBmodificarinfo);
			break;

		case MENUPRODUCTOS:
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_PRODUCTOS), NULL, (DLGPROC)CBproductos);

			break;

		case ID_MENUENVIOS:
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_ENVIO), NULL, (DLGPROC)CBenvios);
			break;

		case IDSALIR:
			mess = MessageBox(handler, "Estas seguro que quieres salir?", "Aviso", MB_YESNO);
			if (mess == IDYES) {
				PostQuitMessage(0);
			}
			break;
		}
	}
	}

	return 0;
}
//vantana alta de envios
BOOL CBaltaenvios(HWND handler, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

	case WM_INITDIALOG: {
		int i = 0;
		productos* buscare = origenp;

		SendDlgItemMessage(handler, IDC_NOMBREVENDEDORE, WM_SETTEXT, sizeof(ingresar->nombrecomp), (LPARAM)ingresar->nombrecomp);
		image = (HBITMAP)LoadImage(NULL, ingresar->direccion, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
		SendMessage(GetDlgItem(handler, IDC_FOTOVENDEDORE), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 0, (LPARAM)"Aguascalintes");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 1, (LPARAM)"Baja California");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 2, (LPARAM)"Baja California Sur");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 3, (LPARAM)"Campeche");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 4, (LPARAM)"Chiapas");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 5, (LPARAM)"Chihuahua");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 6, (LPARAM)"Coahuila");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 7, (LPARAM)"Colima");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 8, (LPARAM)"Durango");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 9, (LPARAM)"Guanajuato");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 10, (LPARAM)"Guerrero");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 11, (LPARAM)"Hidalgo");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 12, (LPARAM)"Jalisco");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 13, (LPARAM)"Estado de Mexico");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 14, (LPARAM)"Michoacan");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 15, (LPARAM)"Morelos");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 16, (LPARAM)"Nayarit");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 17, (LPARAM)"Nuevo Leon");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 18, (LPARAM)"Oaxaca");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 19, (LPARAM)"Puebla");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 20, (LPARAM)"Queretaro");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 21, (LPARAM)"Quintana Roo");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 22, (LPARAM)"San Luis Potosi");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 23, (LPARAM)"Sinaloa");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 24, (LPARAM)"Sonora");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 25, (LPARAM)"Tabasco");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 26, (LPARAM)"Tamaulipas");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 27, (LPARAM)"Tlaxcala");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 28, (LPARAM)"Veracruz");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 29, (LPARAM)"Yucatan");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 30, (LPARAM)"Zacatecas");
		SendMessage(GetDlgItem(handler, IDC_estado), CB_ADDSTRING, 31, (LPARAM)"Cuidad de Mexico");
		do
		{
			SendMessage(GetDlgItem(handler, IDC_COMBO3), CB_ADDSTRING, i, (LPARAM)buscare->nomproducto);
			i++;
			buscare = buscare->sig;

		} while (buscare != NULL);

		break;
	}

	case WM_COMMAND: {
		SYSTEMTIME hoy;
		int picar = LOWORD(wParam);
		int precioint = 0, cantint = 0, cantinvint = 0, error = 0;
		switch (picar) {

		case IDOK:
			SendDlgItemMessage(handler, IDC_COMBO3, WM_GETTEXT, sizeof(ingresare->nproducto), (LPARAM)ingresare->nproducto);
			SendDlgItemMessage(handler, IDC_ecant2, WM_GETTEXT, sizeof(ingresare->cant), (LPARAM)ingresare->cant);
			SendDlgItemMessage(handler, IDC_calle, WM_GETTEXT, sizeof(ingresare->calle), (LPARAM)ingresare->calle);
			SendDlgItemMessage(handler, IDC_colonia, WM_GETTEXT, sizeof(ingresare->colonia), (LPARAM)ingresare->colonia);
			SendDlgItemMessage(handler, IDC_ciudad, WM_GETTEXT, sizeof(ingresare->ciudad), (LPARAM)ingresare->ciudad);
			SendDlgItemMessage(handler, IDC_estado, WM_GETTEXT, sizeof(ingresare->estado), (LPARAM)ingresare->estado);
			SendDlgItemMessage(handler, IDC_mensaje, WM_GETTEXT, sizeof(ingresare->mensaje), (LPARAM)ingresare->mensaje);
			SendDlgItemMessage(handler, IDC_DATETIMEPICKER1, DTM_GETSYSTEMTIME, sizeof(&ingresare->tiempo), (LPARAM)&ingresare->tiempo);
			SendDlgItemMessage(handler, IDC_total, WM_GETTEXT, sizeof(ingresare->total), (LPARAM)ingresare->total);
			GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &ingresare->tiempo, NULL, buf, 200);
			
			GetLocalTime(&hoy);
			if (compararfechas(ingresare->tiempo, hoy) == -1)
			{
				MessageBox(handler, "La fecha de envio debe ser mayor a la fecha actual", "Error", MB_ICONERROR);

			}
			if (ingresare->total[0] == '\0')
			{
				MessageBox(handler, "Presiona el boton precio para obtener el precio a pagar", "Error", MB_ICONERROR);
			}
			// validar la cantida de productos
			buscarppornombre(ingresare->nproducto);
			cantinvint = atoi(buscarp->cantinv);
			precioint = atoi(buscarp->precio);
			cantint = atoi(ingresare->cant);
			if (cantint > cantinvint)
			{
				MessageBox(handler, "Ingresaste mas productos de los que hay en inventario", "Error", MB_ICONERROR);
				error = 1;
			}

			if ((ingresare->nproducto[0] == '\0') || (ingresare->cant[0] == '\0') || (ingresare->calle[0] == '\0') || (ingresare->colonia[0] == '\0') ||
				(ingresare->ciudad[0] == '\0') || (ingresare->mensaje[0] == '\0') || (ingresare->estado[0] == '\0'))
			{
				MessageBox(handler, "Ingresa todos los datos", "Error", MB_ICONERROR);
				error = 1;
			}
			if (error == 0)
			{
				listaEnvios();
				EndDialog(handler, 0);
				DialogBox(ventanas, MAKEINTRESOURCE(IDD_ENVIO), NULL, (DLGPROC)CBenvios);
			}



			break;

		case IDC_botonprecio:

			int total;
			SendDlgItemMessage(handler, IDC_COMBO3, WM_GETTEXT, sizeof(ingresare->nproducto), (LPARAM)ingresare->nproducto);
			SendDlgItemMessage(handler, IDC_ecant2, WM_GETTEXT, sizeof(ingresare->cant), (LPARAM)ingresare->cant);
			buscarppornombre(ingresare->nproducto);
			precioint = atoi(buscarp->precio);
			cantint = atoi(ingresare->cant);
			total = precioint * cantint;
			char totalchar[10];
			_itoa_s(total, totalchar, 10);
			SendDlgItemMessage(handler, IDC_total, WM_SETTEXT, sizeof(totalchar), (LPARAM)totalchar);


			break;


		case ID_VENDEDORES_MODIFICARINFORMACION:
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_INFO), NULL, (DLGPROC)CBinfovendedor);
			break;

		case MENUPRODUCTOS:
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_PRODUCTOS), NULL, (DLGPROC)CBproductos);

			break;

		case ID_MENUENVIOS:
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_ENVIO), NULL, (DLGPROC)CBenvios);
			break;

		case IDSALIR:
			mess = MessageBox(handler, "Estas seguro que quieres salir?", "Aviso", MB_YESNO);
			if (mess == IDYES) {
				PostQuitMessage(0);
			}
			break;
		}
	}
	}

	return 0;
}
//ventana modificar producto
BOOL CBmodificarenvios(HWND handler, UINT message, WPARAM wParam, LPARAM lParam) {
	char auxcant[100];
	int error = 0;
	SendDlgItemMessage(handler, IDC_MODCANTEN, WM_GETTEXT, sizeof(auxcant), (LPARAM)auxcant);

	switch (message){
	case WM_INITDIALOG: {
		int i = 0;
		envios* buscare = origene;

		do
		{
			SendMessage(GetDlgItem(handler, IDC_COMBO4), CB_ADDSTRING, i, (LPARAM)buscare->nproducto);
			i++;
			buscare = buscare->sig;

		} while (buscare != NULL);

		SendDlgItemMessage(handler, IDC_nombremodenvios, WM_SETTEXT, sizeof(ingresar->nombrecomp), (LPARAM)ingresar->nombrecomp);
		image = (HBITMAP)LoadImage(NULL, ingresar->direccion, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
		SendMessage(GetDlgItem(handler, IDC_fotomodenvios), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 0, (LPARAM)"Aguascalintes");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 1, (LPARAM)"Baja California");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 2, (LPARAM)"Baja California Sur");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 3, (LPARAM)"Campeche");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 4, (LPARAM)"Chiapas");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 5, (LPARAM)"Chihuahua");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 6, (LPARAM)"Coahuila");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 7, (LPARAM)"Colima");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 8, (LPARAM)"Durango");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 9, (LPARAM)"Guanajuato");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 10, (LPARAM)"Guerrero");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 11, (LPARAM)"Hidalgo");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 12, (LPARAM)"Jalisco");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 13, (LPARAM)"Estado de Mexico");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 14, (LPARAM)"Michoacan");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 15, (LPARAM)"Morelos");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 16, (LPARAM)"Nayarit");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 17, (LPARAM)"Nuevo Leon");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 18, (LPARAM)"Oaxaca");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 19, (LPARAM)"Puebla");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 20, (LPARAM)"Queretaro");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 21, (LPARAM)"Quintana Roo");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 22, (LPARAM)"San Luis Potosi");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 23, (LPARAM)"Sinaloa");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 24, (LPARAM)"Sonora");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 25, (LPARAM)"Tabasco");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 26, (LPARAM)"Tamaulipas");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 27, (LPARAM)"Tlaxcala");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 28, (LPARAM)"Veracruz");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 29, (LPARAM)"Yucatan");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 30, (LPARAM)"Zacatecas");
		SendMessage(GetDlgItem(handler, IDC_MODESTADOEN), CB_ADDSTRING, 31, (LPARAM)"Cuidad de Mexico");
		
		break;
	}
	case WM_COMMAND: {

		int picar = LOWORD(wParam);

		switch (picar) {
		case IDbuscare: {

			char envionom[200];
			SendDlgItemMessage(handler, IDC_COMBO4, WM_GETTEXT, sizeof(envionom), (LPARAM)envionom);
			buscarepornombre(envionom);

			SendDlgItemMessage(handler, IDC_MODNOMEN, WM_SETTEXT, sizeof(buscare->nproducto), (LPARAM)buscare->nproducto);
			SendDlgItemMessage(handler, IDC_MODCANTEN, WM_SETTEXT, sizeof(buscare->cant), (LPARAM)buscare->cant);
			SendDlgItemMessage(handler, IDC_MODCALLEEN, WM_SETTEXT, sizeof(buscare->calle), (LPARAM)buscare->calle);
			SendDlgItemMessage(handler, IDC_MODCOLONIAEN, WM_SETTEXT, sizeof(buscare->colonia), (LPARAM)buscare->colonia);
			SendDlgItemMessage(handler, IDC_MODCIUDADEN, WM_SETTEXT, sizeof(buscare->ciudad), (LPARAM)buscare->ciudad);
			SendDlgItemMessage(handler, IDC_MODESTADOEN, WM_SETTEXT, sizeof(buscare->estado), (LPARAM)buscare->estado);
			SendDlgItemMessage(handler, IDC_MODMENSAJEEN, WM_SETTEXT, sizeof(buscare->mensaje), (LPARAM)buscare->mensaje);
			SendDlgItemMessage(handler, IDC_DATETIMEPICKER1MOD, DTM_GETSYSTEMTIME, sizeof(&buscare->tiempo), (LPARAM)&buscare->tiempo);
			SendDlgItemMessage(handler, IDC_MODTOTALEN, WM_SETTEXT, sizeof(buscare->total), (LPARAM)buscare->total);


			break;
		}
		case IDmoden: {

			int error = 0;
			char envionom[200];
			int total = 0;
			int precioint = 0, auxcantint = 0;
			char auxnommod[100];
			char totalchar[100], totalcharaux[100];

			SendDlgItemMessage(handler, IDC_MODTOTALEN, WM_GETTEXT, sizeof(totalcharaux), (LPARAM)totalcharaux);
			SendDlgItemMessage(handler, IDC_COMBO4, WM_GETTEXT, sizeof(envionom), (LPARAM)envionom);
			buscarepornombre(envionom);
			SendDlgItemMessage(handler, IDC_COMBO4, WM_GETTEXT, sizeof(auxnommod), (LPARAM)auxnommod);
			buscarppornombre(auxnommod);
			auxcantint = atoi(auxcant);
			total = precioint * auxcantint;
			_itoa_s(total, totalchar, 10);
			
			
			mess = MessageBox(handler, "Desea guardar los cambios?", "Aviso", MB_YESNO);
			if (mess == IDNO) {
				EndDialog(handler, 0);
			}
			else
			{
				//char auxcant[100];
				//if ((strcmp(auxcant, buscare->cant) == 0)&& error == 0)
				if (strcmp(totalchar, totalcharaux) != 0)
				{
					MessageBox(handler, "Se modifico la cantidad de productos por lo tanto cambia el precio", "Error", MB_ICONERROR);
					error = 1;				
				}
				/*if (error == 0 && cantvacnia....)
				{
					error = 1;
				}*/
				if (error == 0)
				{
					SendDlgItemMessage(handler, IDC_MODNOMEN, WM_GETTEXT, sizeof(buscare->nproducto), (LPARAM)buscare->nproducto);
					SendDlgItemMessage(handler, IDC_MODCANTEN, WM_GETTEXT, sizeof(buscare->cant), (LPARAM)buscare->cant);
					SendDlgItemMessage(handler, IDC_MODCALLEEN, WM_GETTEXT, sizeof(buscare->calle), (LPARAM)buscare->calle);
					SendDlgItemMessage(handler, IDC_MODCOLONIAEN, WM_GETTEXT, sizeof(buscare->colonia), (LPARAM)buscare->colonia);
					SendDlgItemMessage(handler, IDC_MODCIUDADEN, WM_GETTEXT, sizeof(buscare->ciudad), (LPARAM)buscare->ciudad);
					SendDlgItemMessage(handler, IDC_MODESTADOEN, WM_GETTEXT, sizeof(buscare->estado), (LPARAM)buscare->estado);
					SendDlgItemMessage(handler, IDC_MODMENSAJEEN, WM_GETTEXT, sizeof(buscare->mensaje), (LPARAM)buscare->mensaje);
					SendDlgItemMessage(handler, IDC_DATETIMEPICKER1MOD, DTM_GETSYSTEMTIME, sizeof(&buscare->tiempo), (LPARAM)&buscare->tiempo);
					SendDlgItemMessage(handler, IDC_MODTOTALEN, WM_GETTEXT, sizeof(buscare->total), (LPARAM)buscare->total);
					EndDialog(handler, 0);
					DialogBox(ventanas, MAKEINTRESOURCE(IDD_ENVIO), NULL, (DLGPROC)CBenvios);
				}



			}


			break;
		}
		case IDpreciomod: {
			int total = 0;
			int precioint = 0, auxcantint = 0;
			char auxnommod[100];
			char totalchar[10];

			SendDlgItemMessage(handler, IDC_COMBO4, WM_GETTEXT, sizeof(auxnommod), (LPARAM)auxnommod);
			buscarppornombre(auxnommod);
			//SendDlgItemMessage(handler, IDC_MODCANTEN, WM_GETTEXT, sizeof(auxcant), (LPARAM)auxcant);
			precioint = atoi(buscarp->precio);
			auxcantint = atoi(auxcant);
			total = precioint * auxcantint;
			_itoa_s(total, totalchar, 10);
			SendDlgItemMessage(handler, IDC_MODTOTALEN, WM_SETTEXT, sizeof(totalchar), (LPARAM)totalchar);
			//strcpy_s(buscare->cant, auxcant);


			break;
		}
		case IDCANCEL: {
			mess = MessageBox(handler, "Cancelar los cambios?", "Aviso", MB_YESNO);
			if (mess == IDNO) {
				EndDialog(handler, 0);
				DialogBox(ventanas, MAKEINTRESOURCE(IDD_ENVIO), NULL, (DLGPROC)CBenvios);

			}
		}


		}

		break;
	}

	 break;
	}


	return 0;
}
// ventana resumen de envio
BOOL CBresumenenvios(HWND handler, UINT message, WPARAM wParam, LPARAM lParam) {
	int i =0 ;

	switch (message)
	{
	case WM_INITDIALOG: {

	envios* buscare = origene;
		
		do
		{
			SendMessage(GetDlgItem(handler, IDC_nombrere), CB_ADDSTRING, i, (LPARAM)buscare->nproducto);
			i++;
			buscare = buscare->sig;

		} while (buscare != NULL);

		SendDlgItemMessage(handler, IDC_NOMBREVENDEDOREre, WM_SETTEXT, sizeof(ingresar->nombrecomp), (LPARAM)ingresar->nombrecomp);
		image = (HBITMAP)LoadImage(NULL, ingresar->direccion, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
		SendMessage(GetDlgItem(handler, IDC_FOTOVENDEDOREre), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);

		break;
	}
	

	case WM_COMMAND:
		int picar = LOWORD(wParam);

		switch (picar)
		{
		case IDvolver: {
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_ENVIO), NULL, (DLGPROC)CBenvios);
			break;
		}
		case IDC_resumenbuscar: {

			char resumenenvionom[200];
			SendDlgItemMessage(handler, IDC_nombrere, WM_GETTEXT, sizeof(resumenenvionom), (LPARAM)resumenenvionom);
			buscarepornombre(resumenenvionom);
			SendDlgItemMessage(handler, IDC_ecantre, WM_SETTEXT, sizeof(buscare->cant), (LPARAM)buscare->cant);
			SendDlgItemMessage(handler, IDC_callere, WM_SETTEXT, sizeof(buscare->calle), (LPARAM)buscare->calle);
			SendDlgItemMessage(handler, IDC_coloniare, WM_SETTEXT, sizeof(buscare->colonia), (LPARAM)buscare->colonia);
			SendDlgItemMessage(handler, IDC_ciudadre, WM_SETTEXT, sizeof(buscare->ciudad), (LPARAM)buscare->ciudad);
			SendDlgItemMessage(handler, IDC_estadore, WM_SETTEXT, sizeof(buscare->estado), (LPARAM)buscare->estado);
			SendDlgItemMessage(handler, IDC_mensajere, WM_SETTEXT, sizeof(buscare->mensaje), (LPARAM)buscare->mensaje);
			SendDlgItemMessage(handler, IDC_DATETIMEPICKER1RE, DTM_GETSYSTEMTIME, sizeof(&buscare->tiempo), (LPARAM)&buscare->tiempo);
			SendDlgItemMessage(handler, IDC_preciore, WM_SETTEXT, sizeof(buscare->total), (LPARAM)buscare->total);

			break;
		}

		 break;
		}


		break;
	}

	return 0;
}
//ventana eliminar envios
BOOL CBeliminarenvios(HWND handler, UINT message, WPARAM wParam, LPARAM lParam) {
	int i = 0;
	switch (message)
	{
	case WM_INITDIALOG: {


		SendDlgItemMessage(handler, IDC_NOMBREVENDEDOREE, WM_SETTEXT, sizeof(ingresar->nombrecomp), (LPARAM)ingresar->nombrecomp);
		image = (HBITMAP)LoadImage(NULL, ingresar->direccion, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
		SendMessage(GetDlgItem(handler, IDC_FOTOVENDEDOREE), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);

		do
		{
			SendMessage(GetDlgItem(handler, IDC_nombreEE), CB_ADDSTRING, i, (LPARAM)buscare->nproducto);
			i++;
			buscare = buscare->sig;

		} while (buscare != NULL);


		break;
	}
	case WM_COMMAND: {
		int picar = LOWORD(wParam);
		switch (picar) {
		
		case IDC_Buscareliminare: {

			char eliminarenvioaux[100];
			SendDlgItemMessage(handler, IDC_nombreEE, WM_GETTEXT, sizeof(eliminarenvioaux), (LPARAM)eliminarenvioaux);
			buscarepornombre(eliminarenvioaux);
			//SendDlgItemMessage(handler, IDC_COMBO3, WM_GETTEXT, sizeof(ingresare->nproducto), (LPARAM)ingresare->nproducto);
			SendDlgItemMessage(handler, IDC_ecantEE, WM_SETTEXT, sizeof(buscare->cant), (LPARAM)buscare->cant);
			SendDlgItemMessage(handler, IDC_calleEE, WM_SETTEXT, sizeof(buscare->calle), (LPARAM)buscare->calle);
			SendDlgItemMessage(handler, IDC_coloniaEE, WM_SETTEXT, sizeof(buscare->colonia), (LPARAM)buscare->colonia);
			SendDlgItemMessage(handler, IDC_ciudadEE, WM_SETTEXT, sizeof(buscare->ciudad), (LPARAM)buscare->ciudad);
			SendDlgItemMessage(handler, IDC_estadoEE, WM_SETTEXT, sizeof(buscare->estado), (LPARAM)buscare->estado);
			SendDlgItemMessage(handler, IDC_mensajeEE, WM_SETTEXT, sizeof(buscare->mensaje), (LPARAM)buscare->mensaje);
			SendDlgItemMessage(handler, IDC_DATETIMEPICKER1EE, DTM_GETSYSTEMTIME, sizeof(&buscare->tiempo), (LPARAM)&buscare->tiempo);
			SendDlgItemMessage(handler, IDC_precioEE, WM_SETTEXT, sizeof(buscare->total), (LPARAM)buscare->total);


			break;
		}
		case IDELIMINARE: {

			//buscare = origene;

			mess = MessageBox(handler, "Estas seguro que quieres eliminar este producto? Ya no podras recuperarlo", "Aviso", MB_YESNO);
			if (mess == IDNO) {
				PostQuitMessage(0);
			}
			else
			{
				while (origene != NULL)
				{

					if (buscare->ant == NULL && buscare->sig == NULL) //Unico NODO
					{
						delete buscare;
						buscare = origene = NULL;
					}
					else if (buscare->ant == NULL) //Primer Nodo
					{
						origene = buscare->sig;
						delete buscare;
						origene->ant = NULL;
						buscare = origene;
					}
					else if (buscare->sig == NULL) //Ultimo Nodo
					{
						buscare->ant->sig = NULL;
						delete buscare;
						buscare = origene;
					}
					else //Nodo de enmedio
					{
						buscare->ant->sig = buscare->sig;
						buscare->sig->ant = buscare->ant;
						delete buscare;
						buscare = origene;
					}
					//buscare = origene;
					EndDialog(handler, 0);
					DialogBox(ventanas, MAKEINTRESOURCE(IDD_ENVIO), NULL, (DLGPROC)CBenvios);


				}

			}




			break;
		}
		case IDCANCEL: {
			EndDialog(handler, 0);
			DialogBox(ventanas, MAKEINTRESOURCE(IDD_ENVIO), NULL, (DLGPROC)CBenvios);

			break;
		}
			break;
		}



		break;
	}
				   break;
	}



	return 0;
}
//ventana filtro de envio
BOOL CBfiltrodeenvios(HWND handler, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message)
	{
		case WM_INITDIALOG: {
			SendDlgItemMessage(handler, IDC_nombrefiltro, WM_SETTEXT, sizeof(ingresar->nombrecomp), (LPARAM)ingresar->nombrecomp);
			image = (HBITMAP)LoadImage(NULL, ingresar->direccion, IMAGE_BITMAP, 80, 100, LR_LOADFROMFILE);
			SendMessage(GetDlgItem(handler, IDC_fotofiltro), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);



			break;
		}
		case WM_COMMAND: {
			int picar = LOWORD(wParam);
			switch (picar) {
				case IDCANCEL: {
					EndDialog(handler, 0);
					DialogBox(ventanas, MAKEINTRESOURCE(IDD_ENVIO), NULL, (DLGPROC)CBenvios);

					break;
				}
				case IDC_buscarfiltro: {

					SYSTEMTIME auxfiltro;
					SendDlgItemMessage(handler, IDC_DATETIMEPICKERfiltro, DTM_GETSYSTEMTIME, sizeof(&auxfiltro), (LPARAM)&auxfiltro);

					if (origene != NULL) {
						actuale = origene;

						do {
							if (auxfiltro.wYear == actuale->tiempo.wYear && auxfiltro.wDay == actuale->tiempo.wDay && auxfiltro.wMonth == actuale->tiempo.wMonth)
							{

								GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &actuale->tiempo, NULL, buf, 200);
								strcpy_s(actuale->aux, "Producto:");
								strcat_s(actuale->aux, actuale->nproducto);
								strcat_s(actuale->aux, " || Cantidad:");
								strcat_s(actuale->aux, actuale->cant);
								strcat_s(actuale->aux, " || Precio: $");
								strcat_s(actuale->aux, actuale->total);
								strcat_s(actuale->aux, " || Fecha de envio:");
								strcat_s(actuale->aux, buf);

								SendDlgItemMessage(handler, IDC_LISTAFILTROS, LB_ADDSTRING, sizeof(actuale->aux), (LPARAM)actuale->aux);
							}


							actuale = actuale->sig;

						} while (actuale != NULL);
					}
					else
					{
						SendDlgItemMessage(handler, IDC_LIST2, LB_ADDSTRING, sizeof("NO HAY ENVIOS EN ESTA FECHA"), (LPARAM)"NO HAY ENVIOS EN ESTA FECHA");
					}

					break;
				}
				break;
			}


			break;
		}
		break;
	}
	return 0;
}

//funciones
int validarCadenas(char cadena[100]) {
	int i = 0, validandoL = 0, j;
	j = strlen(cadena); //se asigna el numero de caracteres que tiene la cadena a J

	while (i < j && validandoL == 0) {

		if (isalpha(cadena[i]) != 0 || cadena[i] == 32) // 32 para que acepte espacios tambien 
		{
			i++; //si es una letra avanza de lo contrario entra al else para salirse del ciclo
		}
		else {
			validandoL = 1;//no son solo letras si te da esto
		}
	}
	return validandoL;
}





