#include "framework.h"
#include "Pia.h"
#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include"resource.h"
#include <string>
#include<fstream>
#include<oleauto.h>
#include<commctrl.h>

using namespace std;
BOOL CALLBACK Principal(HWND ventana, UINT Texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Crear(HWND ventana, UINT Texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Modificar(HWND ventana, UINT Texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Eliminar(HWND ventana, UINT Texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Ver(HWND ventana, UINT Texto, WPARAM wParam, LPARAM lParam);
struct INFO
{
	int NumCita;
	char NombrePaciente[50];
	char hora[50];
	char Dia[50];
	char NombreTratamiento1[50];
	char NombreTratamiento2[50];
	char NombreTratamiento3[50];
	char Descripcion[200];
	int PrecioTratamiento1;
	int PrecioTratamiento2;
	int PrecioTratamiento3;
	int PrecioTotal;
	int dianum;
	SYSTEMTIME fecha;
	SYSTEMTIME HORA;
	INFO* anterior;
	INFO* siguiente;
}*INFORMACION;
INFO* Click = NULL;
SYSTEMTIME date;
SYSTEMTIME e, a;

void LeerInfo();
void AgregarInfoALista(INFO* ejemplo);
void GuardarInfo();
void BorrarEnMemoria();
void ModificarInfo(INFO* buscar, int num, string nomp, string h, string d, string t1, string t2, string t3, string des, int pt1, int pt2, int pt3, int fn, SYSTEMTIME uno, SYSTEMTIME dos);
void BorrarInfo(INFO* del);
INFO* crearcita(int num, string nomp, string h, string d, string t1, string t2, string t3, string des, int pt1, int pt2, int pt3, int fn, SYSTEMTIME uno, SYSTEMTIME dos);
std::wstring s2ws(const std::string& s);
double f1, f2; int fecha1, fecha2;

int WINAPI WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d)
{
	INFORMACION = NULL;
	LeerInfo();
	DialogBox(a, MAKEINTRESOURCE(IDD_PRINCIPAL), NULL, Principal);
	GuardarInfo();
	BorrarEnMemoria();
	return 0;
}
BOOL CALLBACK Principal(HWND ventana, UINT Texto, WPARAM wParam, LPARAM lParam)
{
	switch (Texto)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_CITAS_AGENDARCITA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_CREAR), NULL, Crear);
		}break;
		case ID_CITAS_MODIFICARCITA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_MODIFICAR), NULL, Modificar);
		};
		case ID_CITAS_ELIMINARCITA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ELIMINAR), NULL, Eliminar);
		} break;
		case ID_REVISAR_LISTADECITAS:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_VER), NULL, Ver);
		} break;
		case ID_SALIR_CERRARPROGRAMA:
		{
			DestroyWindow(ventana);
			PostQuitMessage(0);
		}break;
		default:break;
		}

	}break;

	default: break;
	}
	return false;
}
BOOL CALLBACK Crear(HWND ventana, UINT Texto, WPARAM wParam, LPARAM lParam)
{
	switch (Texto)
	{
		f1 = 0;
		f2 = 0;
		fecha1 = 0;
		fecha2 = 0;
	case WM_INITDIALOG:
	{



		DateTime_GetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER1), &date);
		SystemTimeToVariantTime(&date, &f1);

		date.wHour = 0;
		date.wMilliseconds = 0;
		date.wMinute = 0;
		date.wSecond = 0;

		fecha1 = (int)f1;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
		{
			TCHAR Revisar[255];
			GetDlgItemText(ventana, IDC_EDIT2, Revisar, 50);
			int NC = _wtoi(Revisar);

			GetDlgItemText(ventana, IDC_EDIT1, Revisar, 50);
			wstring wnombrep(Revisar);
			string nombrep(wnombrep.begin(), wnombrep.end());

			GetDlgItemText(ventana, IDC_DATETIMEPICKER1, Revisar, 50);
			wstring wdia(Revisar);
			string dia(wdia.begin(), wdia.end());

			DateTime_GetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER1), &date);
			e = date;

			SystemTimeToVariantTime(&date, &f2);

			date.wHour = 0;
			date.wMilliseconds = 0;
			date.wMinute = 0;
			date.wSecond = 0;
			fecha2 = (int)f2;


			GetDlgItemText(ventana, IDC_DATETIMEPICKER2, Revisar, 50);
			DateTime_GetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER2), &date);
			a = date;
			wstring whora(Revisar);
			string hora(whora.begin(), whora.end());

			GetDlgItemText(ventana, IDC_EDIT9, Revisar, 200);
			wstring wdes(Revisar);
			string des(wdes.begin(), wdes.end());

			GetDlgItemText(ventana, IDC_EDIT3, Revisar, 50);
			wstring wnt1(Revisar);
			string nt1(wnt1.begin(), wnt1.end());

			GetDlgItemText(ventana, IDC_EDIT4, Revisar, 50);
			int pt1 = _wtoi(Revisar);

			GetDlgItemText(ventana, IDC_EDIT5, Revisar, 50);
			wstring wnt2(Revisar);
			string nt2(wnt2.begin(), wnt2.end());

			GetDlgItemText(ventana, IDC_EDIT6, Revisar, 50);
			int pt2 = _wtoi(Revisar);

			GetDlgItemText(ventana, IDC_EDIT7, Revisar, 50);
			wstring wnt3(Revisar);
			string nt3(wnt3.begin(), wnt3.end());

			GetDlgItemText(ventana, IDC_EDIT8, Revisar, 50);
			int pt3 = _wtoi(Revisar);
			if (fecha1 >= fecha2)
			{
				MessageBox(ventana, L"No Puedes Ingresar Una Fecha Menor o Igual A La Actual", L"ERROR", 0);
			}
			if (fecha1 < fecha2)
			{
				if (NC != 0)
				{

					if (nombrep != "")
					{
						if (des != "")
						{
							bool confirmacion = true;
							INFO* check = INFORMACION;
							while (check != NULL)
							{
								if (check->NumCita == NC)
								{
									MessageBox(ventana, L"Ya Existe un codigo similar Favor de Ingresar otro", L"ERROR", MB_OK | MB_ICONERROR);
									confirmacion = false;
									break;
								}
								check = check->siguiente;
							}
							if (confirmacion == true)
							{
								INFO* Nuevo = crearcita(NC, nombrep, hora, dia, nt1, nt2, nt3, des, pt1, pt2, pt3, fecha2, e, a);
								AgregarInfoALista(Nuevo);
								MessageBox(ventana, L"Se Creo La Cita", L"complete", MB_OK);
								DestroyWindow(ventana);
								DialogBox(NULL, MAKEINTRESOURCE(IDD_CREAR), NULL, Crear);
							}
						}
						else
						{
							MessageBox(ventana, L"Falta Ingresar una Describcion", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
						}
					}
					else
					{
						MessageBox(ventana, L"Falta Ingresar Nombre Del Paciente", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
					}
				}
				else
				{
					MessageBox(ventana, L"Falta Ingresar Num de Cita", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
				}
			}
		}break;
		case ID_CITAS_AGENDARCITA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_CREAR), NULL, Crear);
		}break;
		case ID_CITAS_MODIFICARCITA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_MODIFICAR), NULL, Modificar);
		};
		case ID_CITAS_ELIMINARCITA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ELIMINAR), NULL, Eliminar);
		} break;
		case ID_REVISAR_LISTADECITAS:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_VER), NULL, Ver);
		} break;
		case ID_SALIR_CERRARPROGRAMA:
		{
			DestroyWindow(ventana);
			PostQuitMessage(0);
		}break;
		default:break;
		}

	}break;

	default: break;
	}
	return false;
}
BOOL CALLBACK Modificar(HWND ventana, UINT Texto, WPARAM wParam, LPARAM lParam)
{
	switch (Texto)
	{
		f1 = 0;
		f2 = 0;
		fecha1 = 0;
		fecha2 = 0;
	case WM_INITDIALOG:
	{
		DateTime_GetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER1), &date);
		SystemTimeToVariantTime(&date, &f1);

		date.wHour = 0;
		date.wMilliseconds = 0;
		date.wMinute = 0;
		date.wSecond = 0;

		fecha1 = (int)f1;

		int fila[500];
		int contador = 0;
		int ciclo = 0;
		wstring wproducto1;
		INFO* orden = INFORMACION;
		int aux;
		while (orden != NULL)
		{

			fila[contador] = orden->dianum;
			contador++;

			ciclo++;
			orden = orden->siguiente;
		}
		for (int i = 0; i < contador; i++)
		{
			for (int j = 0; j < contador; j++)
			{
				if (fila[j] < fila[j + 1])
				{
					aux = fila[j + 1];
					fila[j + 1] = fila[j];
					fila[j] = aux;
				}
			}
		}
		int num = 0;
		for (int i = 0; i < contador; i++)
		{
			INFO* lista = INFORMACION;
			while (lista != NULL)
			{
				if (fila[num] == lista->dianum)
				{
					wproducto1 = s2ws(lista->Dia);
					int posicion = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wproducto1.c_str());
					SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_SETITEMDATA, posicion, (LPARAM)lista);
				}
				lista = lista->siguiente;
			}
			num++;
		}
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_LIST1:
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{ //conseguir info del que se seleciona
				int selecion = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_GETCURSEL, 0, 0);
				Click = (INFO*)SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_GETITEMDATA, selecion, 0);
				//funcion para cargar la info del producto y poder modificarlo
				// mandar la info a sus cuadros
				SetDlgItemText(ventana, IDC_EDIT1, s2ws(Click->NombrePaciente).c_str());
				SetDlgItemText(ventana, IDC_EDIT2, s2ws(to_string(Click->NumCita)).c_str());
				e = Click->fecha;
				a = Click->HORA;

				DateTime_SetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER1), GDT_VALID, &e);
				DateTime_SetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER2), GDT_VALID, &a);
				//SetDlgItemText(ventana, IDC_DATETIMEPICKER1, (LPCWSTR)ddia);
				//SetDlgItemText(ventana, IDC_DATETIMEPICKER2, s2ws(Click->hora).c_str());

				SetDlgItemText(ventana, IDC_EDIT9, s2ws(Click->Descripcion).c_str());
				SetDlgItemText(ventana, IDC_EDIT3, s2ws(Click->NombreTratamiento1).c_str());
				SetDlgItemText(ventana, IDC_EDIT4, s2ws(to_string(Click->PrecioTratamiento1)).c_str());
				SetDlgItemText(ventana, IDC_EDIT5, s2ws(Click->NombreTratamiento2).c_str());
				SetDlgItemText(ventana, IDC_EDIT6, s2ws(to_string(Click->PrecioTratamiento2)).c_str());
				SetDlgItemText(ventana, IDC_EDIT7, s2ws(Click->NombreTratamiento3).c_str());
				SetDlgItemText(ventana, IDC_EDIT8, s2ws(to_string(Click->PrecioTratamiento3)).c_str());

			}break;
			}
		}break;

		case IDC_BUTTON1:
		{
			TCHAR Revisar[255];
			GetDlgItemText(ventana, IDC_EDIT2, Revisar, 50);
			int NC = _wtoi(Revisar);

			GetDlgItemText(ventana, IDC_EDIT1, Revisar, 50);
			wstring wnombrep(Revisar);
			string nombrep(wnombrep.begin(), wnombrep.end());

			GetDlgItemText(ventana, IDC_DATETIMEPICKER1, Revisar, 50);
			wstring wdia(Revisar);
			string dia(wdia.begin(), wdia.end());

			DateTime_GetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER1), &date);
			SystemTimeToVariantTime(&date, &f2);
			date.wHour = 0;
			date.wMilliseconds = 0;
			date.wMinute = 0;
			date.wSecond = 0;
			fecha2 = (int)f2;
			e = date;

			GetDlgItemText(ventana, IDC_DATETIMEPICKER2, Revisar, 50);
			DateTime_GetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER2), &date);
			wstring whora(Revisar);
			string hora(whora.begin(), whora.end());
			a = date;
			GetDlgItemText(ventana, IDC_EDIT9, Revisar, 200);
			wstring wdes(Revisar);
			string des(wdes.begin(), wdes.end());

			GetDlgItemText(ventana, IDC_EDIT3, Revisar, 50);
			wstring wnt1(Revisar);
			string nt1(wnt1.begin(), wnt1.end());

			GetDlgItemText(ventana, IDC_EDIT4, Revisar, 50);
			int pt1 = _wtoi(Revisar);

			GetDlgItemText(ventana, IDC_EDIT5, Revisar, 50);
			wstring wnt2(Revisar);
			string nt2(wnt2.begin(), wnt2.end());

			GetDlgItemText(ventana, IDC_EDIT6, Revisar, 50);
			int pt2 = _wtoi(Revisar);

			GetDlgItemText(ventana, IDC_EDIT7, Revisar, 50);
			wstring wnt3(Revisar);
			string nt3(wnt3.begin(), wnt3.end());

			GetDlgItemText(ventana, IDC_EDIT8, Revisar, 50);
			int pt3 = _wtoi(Revisar);
			if (fecha1 >= fecha2)
			{
				MessageBox(ventana, L"No Puedes Ingresar Una Fecha Menor o Igual A La Actual", L"ERROR", 0);
			}
			if (fecha1 < fecha2)
			{
				if (NC != 0)
				{
					if (nombrep != "")
					{
						if (des != "")
						{
							bool confirmacion = true;
							INFO* check = INFORMACION;
							while (check != NULL)
							{
								if (check->NumCita == NC)
								{
									MessageBox(ventana, L"Ya Existe un codigo similar Favor de Ingresar otro", L"ERROR", MB_OK | MB_ICONERROR);
									confirmacion = false;
									break;
								}
								check = check->siguiente;
							}
							if (confirmacion == true)
							{
								ModificarInfo(Click, NC, nombrep, hora, dia, nt1, nt2, nt3, des, pt1, pt2, pt3, fecha2, e, a);
								DestroyWindow(ventana);
								DialogBox(NULL, MAKEINTRESOURCE(IDD_CREAR), NULL, Crear);
							}
						}
						else
						{
							MessageBox(ventana, L"Falta Ingresar una Describcion", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
						}
					}
					else
					{
						MessageBox(ventana, L"Falta Ingresar Nombre Del Paciente", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
					}
				}
				else
				{
					MessageBox(ventana, L"Falta Ingresar Num de Cita", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
				}
			}
		}break;
		case ID_CITAS_AGENDARCITA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_CREAR), NULL, Crear);
		}break;
		case ID_CITAS_MODIFICARCITA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_MODIFICAR), NULL, Modificar);

		};
		case ID_CITAS_ELIMINARCITA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ELIMINAR), NULL, Eliminar);
		} break;
		case ID_REVISAR_LISTADECITAS:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_VER), NULL, Ver);
		} break;
		case ID_SALIR_CERRARPROGRAMA:
		{
			DestroyWindow(ventana);
			PostQuitMessage(0);
		}break;
		default:break;
		}

	}break;

	default: break;
	}
	return false;
}
BOOL CALLBACK Eliminar(HWND ventana, UINT Texto, WPARAM wParam, LPARAM lParam)
{
	switch (Texto)
	{
	case WM_INITDIALOG:
	{
		DateTime_GetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER1), &date);
		SystemTimeToVariantTime(&date, &f1);

		date.wHour = 0;
		date.wMilliseconds = 0;
		date.wMinute = 0;
		date.wSecond = 0;

		fecha1 = (int)f1;

		int fila[500];
		int contador = 0;
		int ciclo = 0;
		wstring wproducto1;
		INFO* orden = INFORMACION;
		int aux;
		while (orden != NULL)
		{

			fila[contador] = orden->dianum;
			contador++;

			ciclo++;
			orden = orden->siguiente;
		}
		for (int i = 0; i < contador; i++)
		{
			for (int j = 0; j < contador; j++)
			{
				if (fila[j] < fila[j + 1])
				{
					aux = fila[j + 1];
					fila[j + 1] = fila[j];
					fila[j] = aux;
				}
			}
		}
		int num = 0;
		for (int i = 0; i < contador; i++)
		{
			INFO* lista = INFORMACION;
			while (lista != NULL)
			{
				if (fila[num] == lista->dianum)
				{
					wproducto1 = s2ws(lista->Dia);
					int posicion = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wproducto1.c_str());
					SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_SETITEMDATA, posicion, (LPARAM)lista);
				}
				lista = lista->siguiente;
			}
			num++;
		}
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_LIST1:
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{ //conseguir info del que se seleciona
				int selecion = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_GETCURSEL, 0, 0);
				Click = (INFO*)SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_GETITEMDATA, selecion, 0);
				//funcion para cargar la info del producto y poder modificarlo
				// mandar la info a sus cuadros
				SetDlgItemText(ventana, IDC_EDIT1, s2ws(Click->NombrePaciente).c_str());
				SetDlgItemText(ventana, IDC_EDIT2, s2ws(to_string(Click->NumCita)).c_str());
				SetDlgItemText(ventana, IDC_EDIT11, s2ws(Click->Dia).c_str());
				SetDlgItemText(ventana, IDC_EDIT12, s2ws(Click->hora).c_str());
				SetDlgItemText(ventana, IDC_EDIT9, s2ws(Click->Descripcion).c_str());
				SetDlgItemText(ventana, IDC_EDIT3, s2ws(Click->NombreTratamiento1).c_str());
				SetDlgItemText(ventana, IDC_EDIT4, s2ws(to_string(Click->PrecioTratamiento1)).c_str());
				SetDlgItemText(ventana, IDC_EDIT5, s2ws(Click->NombreTratamiento2).c_str());
				SetDlgItemText(ventana, IDC_EDIT6, s2ws(to_string(Click->PrecioTratamiento2)).c_str());
				SetDlgItemText(ventana, IDC_EDIT7, s2ws(Click->NombreTratamiento3).c_str());
				SetDlgItemText(ventana, IDC_EDIT8, s2ws(to_string(Click->PrecioTratamiento3)).c_str());
				SetDlgItemText(ventana, IDC_EDIT10, s2ws(to_string(Click->PrecioTotal)).c_str());

			}break;
			}
		}break;
		case IDC_BUTTON1:
		{
			BorrarInfo(Click);
		}break;
		case ID_CITAS_AGENDARCITA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_CREAR), NULL, Crear);
		}break;
		case ID_CITAS_MODIFICARCITA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_MODIFICAR), NULL, Modificar);
		};
		case ID_CITAS_ELIMINARCITA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ELIMINAR), NULL, Eliminar);
		} break;
		case ID_REVISAR_LISTADECITAS:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_VER), NULL, Ver);
		} break;
		case ID_SALIR_CERRARPROGRAMA:
		{
			DestroyWindow(ventana);
			PostQuitMessage(0);
		}break;
		default:break;
		}

	}break;

	default: break;
	}
	return false;
}
BOOL CALLBACK Ver(HWND ventana, UINT Texto, WPARAM wParam, LPARAM lParam)
{
	switch (Texto)
	{
	case WM_INITDIALOG:
	{
		DateTime_GetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER1), &date);
		SystemTimeToVariantTime(&date, &f1);

		date.wHour = 0;
		date.wMilliseconds = 0;
		date.wMinute = 0;
		date.wSecond = 0;

		fecha1 = (int)f1;

		int fila[500];
		int contador = 0;
		int ciclo = 0;
		wstring wproducto1;
		INFO* orden = INFORMACION;
		int aux;
		while (orden != NULL)
		{

			fila[contador] = orden->dianum;
			contador++;

			ciclo++;
			orden = orden->siguiente;
		}
		for (int i = 0; i < contador; i++)
		{
			for (int j = 0; j < contador; j++)
			{
				if (fila[j] < fila[j + 1])
				{
					aux = fila[j + 1];
					fila[j + 1] = fila[j];
					fila[j] = aux;
				}
			}
		}
		int num = 0;
		for (int i = 0; i < contador; i++)
		{
			INFO* lista = INFORMACION;
			while (lista != NULL)
			{
				if (fila[num] == lista->dianum)
				{
					wproducto1 = s2ws(lista->Dia);
					int posicion = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wproducto1.c_str());
					SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_SETITEMDATA, posicion, (LPARAM)lista);
				}
				lista = lista->siguiente;
			}
			num++;
		}
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_LIST1:
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{ //conseguir info del que se seleciona
				int selecion = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_GETCURSEL, 0, 0);
				Click = (INFO*)SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_GETITEMDATA, selecion, 0);
				//funcion para cargar la info del producto y poder modificarlo
				// mandar la info a sus cuadros
				SetDlgItemText(ventana, IDC_EDIT1, s2ws(Click->NombrePaciente).c_str());
				SetDlgItemText(ventana, IDC_EDIT2, s2ws(to_string(Click->NumCita)).c_str());
				SetDlgItemText(ventana, IDC_EDIT11, s2ws(Click->Dia).c_str());
				SetDlgItemText(ventana, IDC_EDIT12, s2ws(Click->hora).c_str());
				SetDlgItemText(ventana, IDC_EDIT9, s2ws(Click->Descripcion).c_str());
				SetDlgItemText(ventana, IDC_EDIT3, s2ws(Click->NombreTratamiento1).c_str());
				SetDlgItemText(ventana, IDC_EDIT4, s2ws(to_string(Click->PrecioTratamiento1)).c_str());
				SetDlgItemText(ventana, IDC_EDIT5, s2ws(Click->NombreTratamiento2).c_str());
				SetDlgItemText(ventana, IDC_EDIT6, s2ws(to_string(Click->PrecioTratamiento2)).c_str());
				SetDlgItemText(ventana, IDC_EDIT7, s2ws(Click->NombreTratamiento3).c_str());
				SetDlgItemText(ventana, IDC_EDIT8, s2ws(to_string(Click->PrecioTratamiento3)).c_str());
				SetDlgItemText(ventana, IDC_EDIT10, s2ws(to_string(Click->PrecioTotal)).c_str());

			}break;
			}
		}break;
		case ID_CITAS_AGENDARCITA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_CREAR), NULL, Crear);
		}break;
		case ID_CITAS_MODIFICARCITA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_MODIFICAR), NULL, Modificar);
		};
		case ID_CITAS_ELIMINARCITA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ELIMINAR), NULL, Eliminar);
		} break;
		case ID_REVISAR_LISTADECITAS:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_VER), NULL, Ver);
		} break;
		case ID_SALIR_CERRARPROGRAMA:
		{
			DestroyWindow(ventana);
			PostQuitMessage(0);
		}break;
		default:break;
		}

	}break;

	default: break;
	}
	return false;
}
void LeerInfo()
{
	ifstream Leer;
	Leer.open("C:\\Users\\Usuario\\Desktop\\JulioConsulta\\Info.txt", ios::in);
	if (Leer.is_open())
	{
		Leer.seekg(0, Leer.end);
		int archivo = Leer.tellg();
		Leer.seekg(0, Leer.beg);
		int tamao = 0;
		while (tamao < archivo - 2)
		{
			INFO* info = new INFO;
			Leer.read(reinterpret_cast<char*>(info), sizeof(INFO));
			info->siguiente = NULL;
			info->anterior = NULL;
			AgregarInfoALista(info);
			tamao = tamao + sizeof(INFO);
		}
		Leer.close();
	}
}
void AgregarInfoALista(INFO* ejemplo)
{
	if (INFORMACION == NULL)
	{
		INFORMACION = ejemplo;
	}
	else
	{
		INFO* lista = INFORMACION;
		while (lista->siguiente != NULL)
		{
			lista = lista->siguiente;
		}
		lista->siguiente = ejemplo;
		ejemplo->anterior = lista;
	}
}
void GuardarInfo()
{
	ofstream Guardado;
	Guardado.open("C:\\Users\\Usuario\\Desktop\\JulioConsulta\\Info.txt", ios::trunc);
	if (Guardado.is_open())
	{
		INFO* lista = INFORMACION;
		while (lista != NULL)
		{
			Guardado.write((char*)lista, sizeof(INFO));
			lista = lista->siguiente;
		}
		Guardado.close();
	}
}
void BorrarEnMemoria()
{
	INFO* lista = INFORMACION;
	while (lista != NULL)
	{
		INFO* borrar = lista;
		lista = lista->siguiente;
		delete borrar;
	}
	INFORMACION = NULL;
}
void BorrarInfo(INFO* del)
{
	if (INFORMACION == NULL)
	{
		return;
	}
	INFO* borrador = del;
	if (borrador != NULL)
	{
		INFO* Anterior = borrador->anterior;
		INFO* Siguiente = borrador->siguiente;
		if (Anterior == NULL && Siguiente != NULL)
		{
			Siguiente->anterior = NULL;
			delete borrador;
			INFORMACION = Siguiente;
		}
		if (Siguiente == NULL && Anterior != NULL)
		{
			Anterior->siguiente = NULL;
			delete borrador;
		}
		if (Anterior != NULL && Siguiente != NULL)
		{
			Anterior->siguiente = Siguiente;
			Siguiente->anterior = Anterior;
			delete borrador;
		}
		if (Anterior == NULL && Siguiente == NULL)
		{
			if (Anterior == NULL && Siguiente == NULL)
			{
				delete borrador;
			}
			INFORMACION = NULL;
		}
		MessageBox(NULL, L"Se Elimino La Cita", L"SUCCES", MB_OK | MB_ICONERROR);
	}
}
void ModificarInfo(INFO* buscar, int num, string nomp, string h, string d, string t1, string t2, string t3, string des, int pt1, int pt2, int pt3, int fn, SYSTEMTIME uno, SYSTEMTIME dos)
{
	buscar->NumCita = num;
	strcpy_s(buscar->NombrePaciente, 50, nomp.c_str());
	strcpy_s(buscar->hora, 50, h.c_str());
	strcpy_s(buscar->Dia, 50, d.c_str());
	strcpy_s(buscar->NombreTratamiento1, 50, t1.c_str());
	buscar->PrecioTratamiento1 = pt1;
	strcpy_s(buscar->NombreTratamiento2, 50, t2.c_str());
	buscar->PrecioTratamiento2 = pt2;
	strcpy_s(buscar->NombreTratamiento3, 50, t3.c_str());
	buscar->PrecioTratamiento3 = pt3;
	buscar->PrecioTotal = buscar->PrecioTratamiento1 + buscar->PrecioTratamiento2 + buscar->PrecioTratamiento3;
	buscar->dianum = fn;
	strcpy_s(buscar->Descripcion, 200, des.c_str());
	buscar->fecha = uno;
	buscar->HORA = dos;
}
INFO* crearcita(int num, string nomp, string h, string d, string t1, string t2, string t3, string des, int pt1, int pt2, int pt3, int fn, SYSTEMTIME uno, SYSTEMTIME dos)
{
	INFO* Agregar = new INFO;
	Agregar->NumCita = num;
	strcpy_s(Agregar->NombrePaciente, 50, nomp.c_str());
	strcpy_s(Agregar->hora, 50, h.c_str());
	strcpy_s(Agregar->Dia, 50, d.c_str());
	strcpy_s(Agregar->NombreTratamiento1, 50, t1.c_str());
	Agregar->PrecioTratamiento1 = pt1;
	strcpy_s(Agregar->NombreTratamiento2, 50, t2.c_str());
	Agregar->PrecioTratamiento2 = pt2;
	strcpy_s(Agregar->NombreTratamiento3, 50, t3.c_str());
	Agregar->PrecioTratamiento3 = pt3;
	Agregar->PrecioTotal = Agregar->PrecioTratamiento1 + Agregar->PrecioTratamiento2 + Agregar->PrecioTratamiento3;
	Agregar->dianum = fn;
	strcpy_s(Agregar->Descripcion, 200, des.c_str());
	Agregar->fecha = uno;
	Agregar->HORA = dos;
	Agregar->anterior = NULL;
	Agregar->siguiente = NULL;

	return Agregar;
}

std::wstring s2ws(const std::string& s) {
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
