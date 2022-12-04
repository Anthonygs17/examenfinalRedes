def imprimirCamino(verticeActual, ancestros, caminoString):
    if verticeActual == -1:
        return caminoString
    caminoString = imprimirCamino(ancestros[verticeActual], ancestros, caminoString)
    caminoString += str(verticeActual) + ' -> '
    return caminoString


def imprimirSolucion(verticeInicial, distancias, ancestros):
    numeroVertices = len(distancias)
    print('-' * 60)
    print('|{0: ^13}|{1: ^13}|{2: ^30}|'.format('Vértice', 'Distancia', 'Camino'))
    print('-' * 60, end='')
    for indiceVertice in range(numeroVertices):
        if indiceVertice != verticeInicial:
            verticeString = str(verticeInicial) + ' -> ' + str(indiceVertice)
            distanciaString = str(distancias[indiceVertice])
            caminoString = ' '
            caminoString = imprimirCamino(indiceVertice, ancestros, caminoString)
            print()
            print('|{0: ^13}|{1: ^13}|{2: <30}|'.format(verticeString, distanciaString, caminoString), end='')
    print()
    print('-' * 60, end='')


def dijkstra(matriz, verticeInicial):
    numeroVertices = len(matriz[0])
    distanciasMenores = [float('inf')] * numeroVertices
    agregados = [False] * numeroVertices

    for indiceVertice in range(numeroVertices):
        distanciasMenores[indiceVertice] = float('inf')
        agregados[indiceVertice] = False

    distanciasMenores[verticeInicial] = 0
    ancestros = [-1] * numeroVertices
    ancestros[verticeInicial] = -1

    for i in range(1, numeroVertices):
        verticeCercano = -1
        distanciaMinima = float('inf')
        for indiceVertice in range(numeroVertices):
            if not agregados[indiceVertice] and distanciasMenores[indiceVertice] < distanciaMinima:
                verticeCercano = indiceVertice
                distanciaMinima = distanciasMenores[indiceVertice]

        agregados[verticeCercano] = True

        for indiceVertice in range(numeroVertices):
            distanciaArista = matriz[verticeCercano][indiceVertice]
            if distanciaArista > 0 and ((distanciaMinima + distanciaArista) < distanciasMenores[indiceVertice]):
                ancestros[indiceVertice] = verticeCercano
                distanciasMenores[indiceVertice] = distanciaMinima + distanciaArista

    imprimirSolucion(verticeInicial, distanciasMenores, ancestros)


if __name__ == '__main__':
    
    ### TORUS 1D
    topologiaTorus1D = [[0, 1, 0, 0, 0, 0, 0, 0, 34],#1
                        [1, 0, 1, 0, 0, 0, 0, 0, 0],#2
                        [0, 1, 0, 2, 0, 0, 0, 0, 0],#3
                        [0, 0, 2, 0, 3, 0, 0, 0, 0],#4
                        [0, 0, 0, 3, 0, 5, 0, 0, 0],#5
                        [0, 0, 0, 0, 5, 0, 8, 0, 0],#6
                        [0, 0, 0, 0, 0, 8, 0, 13, 0],#7
                        [0, 0, 0, 0, 0, 0, 13, 0, 21],#8
                        [34, 0, 0, 0, 0, 0, 0, 21, 0]]#9
    
    ### TORUS 2D
    topologiaTorus2D = [[0, 1, 2, 3, 0, 0, 144, 0, 0],#1
                        [1, 0, 1, 0, 377, 0, 0, 233, 0],#2
                        [2, 1, 0, 0, 0, 1597, 0, 0, 987],#3
                        [3, 0, 0, 0, 5, 13, 21, 0, 0],#4
                        [0, 377, 0, 5, 0, 8, 0, 610, 0],#5
                        [0, 0, 1597, 13, 8, 0, 0, 0, 2584],#6
                        [144, 0, 0, 21, 0, 0, 0, 34, 89],#7
                        [0, 233, 0, 0, 610, 0, 34, 0, 55],#8
                        [0, 0, 987, 0, 0, 2584, 89, 55, 0]]#9
    

    dijkstra(topologiaTorus2D, 0)
