
void insertartEnPos(double *apo, int pos)
{
	int idx = pos - 1;
	int padre;

	/*
		Evaluamos si el arbol es par o impar.
		Si es idx 1 (3 elementos), la raiz-padre es el apo[0], apo[idx] es un nodo hoja
	*/
	if (idx > 0)
	{
		if (idx % 2 == 0)
		{
			padre = (idx - 2) / 2;
		}
		else
		{
			padre = (idx - 1) / 2;
		}
	}

	/*
	Se compara el nodo idx con el padre, si el padre es mayor se empuja hacia abajo del arbol siendo este un nodo idx *hoja.
	*/
	if (apo[padre] > apo[idx])
	{
		double tmp = apo[idx];
		apo[idx] = apo[padre];
		apo[padre] = tmp;

		// Una vez intercambiado, se va al nodo de al lado para compararlo.
		insertarEnPos(apo, padre + 1);
	}
}

void HeapSort(*v, n)
{
	double *apo = new double[n];
	int tamapo = 0;

	for (int i = 0; i < n; i++)
	{
		apo[tamapo] = v[i];
		tamapo++;
		insertartEnPos(apo, tamapo);
	}
	/*Recogemos los datos ordenados*/
	for (int i = 0; i < n; i++)
	{
		// cogemos la raiz que es el numero mas pequenio.
		v[i] = apo[0];
		tamapo--; // Reducimos el arbol
		/*Reestructuramos el arbol a un tamanio mas pequenio*/
		reestructurarRaiz(apo, 0, tamapo);
	}

	delete[] apo;
}

void reestructurarRaiz(double *apo, int pos, int tamapo)
{
	int minhijo;
	if (2 * pos + 1 < tamapo)
	{
		minhijo = 2 * pos + 1;
		if ((minhijo + 1 < tamapo) && (apo[minhijo] > apo[minhijo + 1]))
			minhijo++;
		if (apo[pos] > apo[minhijo])
		{
			double tmp = apo[pos];
			apo[pos] = apo[minhijo];
			apo[minhijo] = tmp;
			reestructurarRaiz(apo, minhijo, tamapo);
		}
	}
}