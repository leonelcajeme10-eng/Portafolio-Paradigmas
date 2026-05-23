% ============================================================
% SESIÓN 3 - Aplicación 2: El Mono y la Banana
% Paradigma Lógico - Planificación con estados
% ============================================================
% Para ejecutar: swipl mono_banana.pl
% Consulta: ?- resolver.
% ============================================================

% ============================================================
% DESCRIPCIÓN DEL PROBLEMA
% ============================================================
% Un mono está en la puerta de una habitación.
% En el centro de la habitación cuelga un racimo de bananas
% del techo, fuera del alcance del mono.
% Hay una caja en la ventana de la habitación.
% El mono puede:
%   - Caminar por el cuarto
%   - Empujar la caja a una posición
%   - Subirse a la caja
%   - Agarrar las bananas (si está en el centro sobre la caja)
%
% Estado: estado(PosMonico, EnCaja, PosCaja, TieneBanana)
%   PosMonico : puerta | ventana | centro
%   EnCaja    : si | no
%   PosCaja   : puerta | ventana | centro
%   TieneBanana: si | no
% ============================================================

% ============================================================
% ESTADO INICIAL Y OBJETIVO
% ============================================================

% Estado inicial: mono en puerta, no está en caja,
%                 caja en ventana, no tiene banana
estado_inicial(estado(puerta, no, ventana, no)).

% Estado objetivo: el mono tiene la banana
objetivo(estado(_, _, _, si)).

% ============================================================
% ACCIONES (Operadores)
% ============================================================

% Acción: caminar(Desde, Hasta)
% El mono puede caminar si NO está sobre la caja
puede_hacer(
    estado(Desde, no, PosCaja, Banana),
    caminar(Desde, Hasta),
    estado(Hasta, no, PosCaja, Banana)
) :-
    lugar(Desde),
    lugar(Hasta),
    Desde \= Hasta.

% Acción: empujar_caja(Lugar, Destino)
% El mono puede empujar la caja si está en el mismo lugar que ella
puede_hacer(
    estado(Lugar, no, Lugar, Banana),
    empujar_caja(Lugar, Destino),
    estado(Destino, no, Destino, Banana)
) :-
    lugar(Lugar),
    lugar(Destino),
    Lugar \= Destino.

% Acción: subir_caja
% El mono puede subirse a la caja si está en el mismo lugar
puede_hacer(
    estado(Lugar, no, Lugar, Banana),
    subir_caja,
    estado(Lugar, si, Lugar, Banana)
) :-
    lugar(Lugar).

% Acción: bajar_caja
% El mono puede bajar de la caja
puede_hacer(
    estado(Lugar, si, Lugar, Banana),
    bajar_caja,
    estado(Lugar, no, Lugar, Banana)
) :-
    lugar(Lugar).

% Acción: agarrar_banana
% El mono puede agarrar la banana si está en el centro sobre la caja
puede_hacer(
    estado(centro, si, centro, no),
    agarrar_banana,
    estado(centro, si, centro, si)
).

% ============================================================
% LUGARES VÁLIDOS
% ============================================================

lugar(puerta).
lugar(ventana).
lugar(centro).

% ============================================================
% BÚSQUEDA DE SOLUCIÓN (BFS con lista de visitados)
% ============================================================

% resuelve(EstadoActual, Plan, Visitados)
resuelve(Estado, [], _) :-
    objetivo(Estado).

resuelve(Estado, [Accion|Resto], Visitados) :-
    puede_hacer(Estado, Accion, SigEstado),
    \+ member(SigEstado, Visitados),
    resuelve(SigEstado, Resto, [SigEstado|Visitados]).

% ============================================================
% PREDICADO PRINCIPAL CON PRESENTACIÓN
% ============================================================

resolver :-
    estado_inicial(Inicio),
    format("~n============================================~n"),
    format("   EL MONO Y LA BANANA - Solución~n"),
    format("============================================~n"),
    format("Estado inicial: ~w~n~n", [Inicio]),
    (   resuelve(Inicio, Plan, [Inicio])
    ->  format("¡Solución encontrada!~n~n"),
        format("Plan de acciones:~n"),
        imprimir_plan(Plan, 1),
        length(Plan, N),
        format("~nTotal de pasos: ~w~n", [N]),
        format("~n¡El mono obtuvo las bananas!~n")
    ;   format("No se encontró solución.~n")
    ).

% Imprimir el plan numerado
imprimir_plan([], _).
imprimir_plan([Accion|Resto], N) :-
    format("  Paso ~w: ~w~n", [N, Accion]),
    N1 is N + 1,
    imprimir_plan(Resto, N1).

% ============================================================
% VERSIÓN DETALLADA: muestra estado en cada paso
% ============================================================

resolver_detallado :-
    estado_inicial(Inicio),
    format("~n============================================~n"),
    format("   EL MONO Y LA BANANA - Detallado~n"),
    format("============================================~n"),
    format("Leyenda del estado:~n"),
    format("  estado(PosMonico, EnCaja, PosCaja, TieneBanana)~n~n"),
    format("Estado inicial: ~w~n", [Inicio]),
    (   resuelve(Inicio, Plan, [Inicio])
    ->  ejecutar_plan(Inicio, Plan, 1)
    ;   format("No se encontró solución.~n")
    ).

ejecutar_plan(Estado, [], _) :-
    format("~nEstado final: ~w~n", [Estado]),
    format("¡Objetivo alcanzado! El mono tiene la banana.~n").

ejecutar_plan(Estado, [Accion|Resto], N) :-
    puede_hacer(Estado, Accion, SigEstado),
    format("~nPaso ~w: ~w~n", [N, Accion]),
    format("  Estado: ~w~n", [SigEstado]),
    N1 is N + 1,
    ejecutar_plan(SigEstado, Resto, N1).

% ============================================================
% CONSULTAS DE EJEMPLO
% ============================================================
% ?- resolver.
% ?- resolver_detallado.
% ?- estado_inicial(E), resuelve(E, Plan, [E]), length(Plan, N).
