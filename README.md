# Pivot Stations Problem

Questo repository  contiene la risoluzione al *Pivot Stations Problem*.

Di seguito l'analisi del problema e della risoluzione.

Linguaggio utilizzato: **C++ 14**

----

### Definizioni

##### Movement Graph 

Si tratta di un grafo diretto aciclico (*DAG*), che rappresenta tutti i possibili percorsi percorribili da un treno.
I nodi del grafo rappresentano le *stazioni*, mentre gli archi i possibili *tratti* del percorso che collegano due stazioni.
Ci possono essere situazioni in cui il treno può dover scegliere tra più tratti per raggiungere la stazione successiva.

##### Pivot Station

Si tratta di una stazione che, a prescindere dal percorso scelto dal treno per andare da S<sub>o</sub> a S<sub>d</sub>, non può essere bypassata. 
In altre parole, tale stazione sarà presente in tutti i percorsi possibili tra S<sub>o</sub>  e S<sub>d</sub>.

**Nota**: per semplicità, considero come Pivot Stations anche la stazione di partenza e quella di arrivo.

### Problema

Dato un *Movement Graph* `m`, una stazione di partenza S<sub>o</sub> e una destinazione S<sub>d</sub>, trovare le Pivot Stations del grafo.

### Implementazione

- Inizialmente mi sono concentrato sulla definizione del *Movement Graph*: ho creato una classe `MovementGraph` che rappresenta il grafo tramite una lista di `Station`, una struttura che include un id numerico e una lista di possibili `Track`, che collegano la stazione ad un'altra stazione specificata.
- In seguito ho definito la ricerca dei percorsi possibili da una stazione di partenza ad una di arrivo, implementando l'algoritmo di *Depth First Search*(metodo `recursive_dfs()`), che ricorsivamente visita ciascun nodo (stazione) del grafo, analizzandone gli archi (i track) costruendo la lista di percorsi, con un principio simile agli algoritmi di backtracking, ovvero torna indietro nel percorso, aggiungendoci nuovi nodi raggiungibili per vedere se si può arrivare alla destinazione.
- Ho infine implementato due strategie per la ricerca delle Pivot Station dati S<sub>o</sub>, S<sub>d</sub> e la lista di percorsi possibili:
  - **Strategia 1**:  (metodo `MovementGraph::findPivotStations_strategy1()`)
    Una volta trovati i percorsi che portano da S<sub>o</sub> a S<sub>d</sub> cerco le stazioni che sono presenti in tutti i percorsi.
  - **Strategia 2**: (metodo `MovementGraph::findPivotStations_strategy2()`) 
    Elimino una alla volta le stazioni del grafo e cerco i percorsi da S<sub>o</sub> a S<sub>d</sub>: se non ne trovo la stazione eliminata è pivot.



### Esecuzione

Nell'esempio del testo, senza considerare le stazioni di partenza e arrivo (S<sub>0</sub> e  S<sub>6</sub>) non sono presenti altre Pivot Station, in quanto per ogni stazione S<sub>i</sub> in [S<sub>1</sub>, S<sub>5</sub>] esiste almeno un percorso tra S<sub>0</sub> e S<sub>6</sub> che non include S_i:

![](https://github.com/fabridigua/pivot-stations-problem/blob/main/movement_graph_esempio_1.png)

Esecuzione algoritmo:
```
[Strategy 1] Pivot Stations found between S0 and S6:
S0
S6

[Strategy 2] Pivot Stations found between S0 and S6:
S0
S6
```

Tuttavia se elimino **T<sub>12</sub>**, la stazione S<sub>5</sub> diventa una Pivot Station:

![](https://github.com/fabridigua/pivot-stations-problem/blob/main/movement_graph_esempio_1_noT12.png)

Esecuzione:

```
[Strategy 1] Pivot Stations found between S0 and S6:
S0
S5
S6

[Strategy 2] Pivot Stations found between S0 and S6:
S0
S5
S6
```

Per testare maggiormente il codice ho costruito un ulteriore *Movement Graph*, leggermente più complesso:

![](https://github.com/fabridigua/pivot-stations-problem/blob/main/movement_graph_esempio_2.png)

in cui mi aspetto che le stazioni pivot siano  S<sub>0</sub>, S<sub>1</sub>, S<sub>6</sub>, S<sub>7</sub> e S<sub>10</sub>. Infatti:

```
[Strategy 1] Pivot Stations found between S0 and S10:
S0
S1
S6
S7
S10

[Strategy 2] Pivot Stations found between S0 and S10:
S0
S1
S6
S7
S10
```

### Analisi complessità

L'algoritmo di DFS da sè ha complessità **O(V+E)**, dove V è l'insieme dei nodi (stazioni) del grafo ed E l'insieme degli archi (tratti).

Questo perchè dipende dal numero di visite ai nodi effettuate durante la ricerca: nel caso peggiore da ogni stazione si può raggiungere ogni altra stazione, portando la complessità a V + E.

**Strategia 1:**

Nel corpo principale, oltre alla DFS, faccio un ciclo annidato che dipende dal numero di stazioni V e da quello dei path trovati:

```
for (const auto& s : _stations)
{
    bool is_pivot = true;
    // 1.1 Cicli i percorsi da S-o a S-d
    for (auto p : paths_found)
    {
        // 1.2 Estraggo le stazioni del percorso
        auto path_stations = get_station_list(p);
        // 1.3 Cerco la stazione
        if ((std::find(path_stations.begin(), path_stations.end(), s._id) == path_stations.end()))
        {
            is_pivot = false;
            break;
        }          
    }      
    if (is_pivot) pivots.emplace_back(s._id);      
}
```
Per il ciclo interno ipotizzo un costo O(1).
Il numero dei percorsi trovati, che chiamo P, dipende dal numero di stazioni V.
Questo può essere stimato pensando che nel caso peggiore da ogni stazione è possibile raggiungere la destinazione passando per ogni altro nodo; dunque P= O(V<sup>2</sup>)
Considerando che ciclo i percorsi percorribili per ogni stazione, la complessità viene **O(V<sup>3</sup>)**.



**Strategia 2:**

Nel corpo principale chiamo iterativamente la DFS per ogni stazione del grafo, con tuttavia non V nodi, ma V-1:
```
for (const auto& s : _stations)
{
    int s_id = s._id;
    // 1.1 Rimuovo momentaneamente la stazione dal grafo
    removeStation(s_id);
    
    // 1.2 Calcolo di nuovo tutti i percorsi possibili da S_o a S_d nel grafo privo della stazione s
    auto paths_found = get_feasable_paths(S_o, S_d);

    // 1.3 Se non ho trovato percorsi dopo aver rimosso la stazione s, è una Pivot Station
    if(paths_found.size() == 0)
        pivots.emplace_back(s_id);

    // 1.4 Ripristino la lista di stazioni
    _stations = stations_backup;
}
```
La complessità dunque è data da **O( (V -1 + E) * V)** ovvero **O(V^2 + V*E)**, dove V è il numero di nodi, E gli archi.



