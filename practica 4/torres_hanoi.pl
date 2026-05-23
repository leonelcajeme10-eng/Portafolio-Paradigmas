% ============================================================
% SESIÓN 3 - Aplicación 1: Torres de Hanoi
% Paradigma Lógico
% ============================================================
% Para ejecutar: swipl torres_hanoi.pl
% Consulta: ?- hanoi(3, izquierda, derecha, centro).
% ============================================================

% hanoi(N, Origen, Destino, Auxiliar)
% N         = número de discos
% Origen    = poste de inicio
% Destino   = poste de destino
% Auxiliar  = poste auxiliar

hanoi(1, Origen, Destino, _) :-
    format("Mover disco 1 de ~w a ~w~n", [Origen, Destino]).

hanoi(N, Origen, Destino, Auxiliar) :-
    N > 1,
    N1 is N - 1,
    % Paso 1: mover N-1 discos del origen al auxiliar
    hanoi(N1, Origen, Auxiliar, Destino),
    % Paso 2: mover el disco N del origen al destino
    format("Mover disco ~w de ~w a ~w~n", [N, Origen, Destino]),
    % Paso 3: mover N-1 discos del auxiliar al destino
    hanoi(N1, Auxiliar, Destino, Origen).

% ============================================================
% Versión que cuenta los movimientos
% ============================================================

hanoi_cuenta(1, Origen, Destino, _, Movs, Movs1) :-
    format("  Paso ~w: Mover disco 1 de [~w] --> [~w]~n", [Movs, Origen, Destino]),
    Movs1 is Movs + 1.

hanoi_cuenta(N, Origen, Destino, Auxiliar, Movs0, MovsF) :-
    N > 1,
    N1 is N - 1,
    hanoi_cuenta(N1, Origen, Auxiliar, Destino, Movs0, Movs1),
    format("  Paso ~w: Mover disco ~w de [~w] --> [~w]~n", [Movs1, N, Origen, Destino]),
    Movs2 is Movs1 + 1,
    hanoi_cuenta(N1, Auxiliar, Destino, Origen, Movs2, MovsF).

% ============================================================
% Versión que colecciona movimientos en una lista
% ============================================================

% hanoi_lista(N, Origen, Destino, Auxiliar, ListaMovimientos)
hanoi_lista(1, O, D, _, [mover(1, O, D)]).
hanoi_lista(N, O, D, A, Movs) :-
    N > 1,
    N1 is N - 1,
    hanoi_lista(N1, O, A, D, Movs1),
    hanoi_lista(N1, A, D, O, Movs2),
    append(Movs1, [mover(N, O, D)|Movs2], Movs).

% Calcular el número de movimientos mínimos: 2^N - 1
movimientos_minimos(N, M) :-
    M is 2^N - 1.

% ============================================================
% Predicado principal con presentación
% ============================================================

resolver_hanoi(N) :-
    format("~n========================================~n"),
    format("   TORRES DE HANOI - ~w Disco(s)~n", [N]),
    format("========================================~n"),
    format("Postes: Izquierda (I), Centro (C), Derecha (D)~n~n"),
    format("Secuencia de movimientos:~n"),
    hanoi_cuenta(N, izquierda, derecha, centro, 1, Total),
    T is Total - 1,
    movimientos_minimos(N, Min),
    format("~nTotal de movimientos realizados: ~w~n", [T]),
    format("Movimientos mínimos (2^~w - 1): ~w~n", [N, Min]).

% ============================================================
% CONSULTAS DE EJEMPLO
% ============================================================
% --- Versión básica ---
% ?- hanoi(3, izquierda, derecha, centro).
%
% --- Versión con conteo ---
% ?- resolver_hanoi(3).
% ?- resolver_hanoi(4).
%
% --- Obtener lista de movimientos ---
% ?- hanoi_lista(3, i, d, c, L), length(L, N).
%
% --- Solo calcular movimientos mínimos ---
% ?- movimientos_minimos(10, M).
