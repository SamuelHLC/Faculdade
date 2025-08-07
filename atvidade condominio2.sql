--
-- PostgreSQL database dump
--

-- Dumped from database version 17.5
-- Dumped by pg_dump version 17.5

-- Started on 2025-07-09 14:27:40

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 6 (class 2615 OID 16635)
-- Name: reservas; Type: SCHEMA; Schema: -; Owner: postgres
--

CREATE SCHEMA reservas;


ALTER SCHEMA reservas OWNER TO postgres;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 223 (class 1259 OID 16688)
-- Name: agenda_reservas; Type: TABLE; Schema: reservas; Owner: postgres
--

CREATE TABLE reservas.agenda_reservas (
    id_reserva integer NOT NULL,
    id_morador integer,
    id_espaco integer,
    data_reserva date NOT NULL,
    horario time without time zone NOT NULL
);


ALTER TABLE reservas.agenda_reservas OWNER TO postgres;

--
-- TOC entry 222 (class 1259 OID 16687)
-- Name: agenda_reservas_id_reserva_seq; Type: SEQUENCE; Schema: reservas; Owner: postgres
--

CREATE SEQUENCE reservas.agenda_reservas_id_reserva_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE reservas.agenda_reservas_id_reserva_seq OWNER TO postgres;

--
-- TOC entry 4925 (class 0 OID 0)
-- Dependencies: 222
-- Name: agenda_reservas_id_reserva_seq; Type: SEQUENCE OWNED BY; Schema: reservas; Owner: postgres
--

ALTER SEQUENCE reservas.agenda_reservas_id_reserva_seq OWNED BY reservas.agenda_reservas.id_reserva;


--
-- TOC entry 221 (class 1259 OID 16659)
-- Name: espacos; Type: TABLE; Schema: reservas; Owner: postgres
--

CREATE TABLE reservas.espacos (
    id_espaco integer NOT NULL,
    nome character varying(50) NOT NULL,
    capacidade_maxima integer NOT NULL,
    reserva_unica boolean DEFAULT false
);


ALTER TABLE reservas.espacos OWNER TO postgres;

--
-- TOC entry 220 (class 1259 OID 16658)
-- Name: espacos_id_espaco_seq; Type: SEQUENCE; Schema: reservas; Owner: postgres
--

CREATE SEQUENCE reservas.espacos_id_espaco_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE reservas.espacos_id_espaco_seq OWNER TO postgres;

--
-- TOC entry 4926 (class 0 OID 0)
-- Dependencies: 220
-- Name: espacos_id_espaco_seq; Type: SEQUENCE OWNED BY; Schema: reservas; Owner: postgres
--

ALTER SEQUENCE reservas.espacos_id_espaco_seq OWNED BY reservas.espacos.id_espaco;


--
-- TOC entry 219 (class 1259 OID 16652)
-- Name: moradores; Type: TABLE; Schema: reservas; Owner: postgres
--

CREATE TABLE reservas.moradores (
    id_morador integer NOT NULL,
    nome_completo character varying(100) NOT NULL,
    apartamento character varying(10) NOT NULL,
    bloco character varying(10) NOT NULL,
    telefone character varying(20),
    email character varying(100)
);


ALTER TABLE reservas.moradores OWNER TO postgres;

--
-- TOC entry 218 (class 1259 OID 16651)
-- Name: moradores_id_morador_seq; Type: SEQUENCE; Schema: reservas; Owner: postgres
--

CREATE SEQUENCE reservas.moradores_id_morador_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE reservas.moradores_id_morador_seq OWNER TO postgres;

--
-- TOC entry 4927 (class 0 OID 0)
-- Dependencies: 218
-- Name: moradores_id_morador_seq; Type: SEQUENCE OWNED BY; Schema: reservas; Owner: postgres
--

ALTER SEQUENCE reservas.moradores_id_morador_seq OWNED BY reservas.moradores.id_morador;


--
-- TOC entry 4756 (class 2604 OID 16691)
-- Name: agenda_reservas id_reserva; Type: DEFAULT; Schema: reservas; Owner: postgres
--

ALTER TABLE ONLY reservas.agenda_reservas ALTER COLUMN id_reserva SET DEFAULT nextval('reservas.agenda_reservas_id_reserva_seq'::regclass);


--
-- TOC entry 4754 (class 2604 OID 16662)
-- Name: espacos id_espaco; Type: DEFAULT; Schema: reservas; Owner: postgres
--

ALTER TABLE ONLY reservas.espacos ALTER COLUMN id_espaco SET DEFAULT nextval('reservas.espacos_id_espaco_seq'::regclass);


--
-- TOC entry 4753 (class 2604 OID 16655)
-- Name: moradores id_morador; Type: DEFAULT; Schema: reservas; Owner: postgres
--

ALTER TABLE ONLY reservas.moradores ALTER COLUMN id_morador SET DEFAULT nextval('reservas.moradores_id_morador_seq'::regclass);


--
-- TOC entry 4919 (class 0 OID 16688)
-- Dependencies: 223
-- Data for Name: agenda_reservas; Type: TABLE DATA; Schema: reservas; Owner: postgres
--

COPY reservas.agenda_reservas (id_reserva, id_morador, id_espaco, data_reserva, horario) FROM stdin;
1	1	1	2025-07-15	18:00:00
2	2	2	2025-07-16	19:00:00
3	3	3	2025-07-15	20:00:00
4	4	4	2025-07-15	10:00:00
5	1	3	2025-07-16	21:00:00
6	2	4	2025-07-16	09:00:00
\.


--
-- TOC entry 4917 (class 0 OID 16659)
-- Dependencies: 221
-- Data for Name: espacos; Type: TABLE DATA; Schema: reservas; Owner: postgres
--

COPY reservas.espacos (id_espaco, nome, capacidade_maxima, reserva_unica) FROM stdin;
1	Salão de Festas	50	t
2	Espaço Gourmet	20	t
3	Cinema	15	f
4	Área de Beleza	5	f
\.


--
-- TOC entry 4915 (class 0 OID 16652)
-- Dependencies: 219
-- Data for Name: moradores; Type: TABLE DATA; Schema: reservas; Owner: postgres
--

COPY reservas.moradores (id_morador, nome_completo, apartamento, bloco, telefone, email) FROM stdin;
1	Ana Silva	101	A	11999999999	ana.silva@email.com
2	Bruno Souza	202	B	11988888888	bruno.souza@email.com
3	Carlos Lima	303	C	11977777777	carlos.lima@email.com
4	Daniela Rocha	404	D	11966666666	daniela.rocha@email.com
\.


--
-- TOC entry 4928 (class 0 OID 0)
-- Dependencies: 222
-- Name: agenda_reservas_id_reserva_seq; Type: SEQUENCE SET; Schema: reservas; Owner: postgres
--

SELECT pg_catalog.setval('reservas.agenda_reservas_id_reserva_seq', 6, true);


--
-- TOC entry 4929 (class 0 OID 0)
-- Dependencies: 220
-- Name: espacos_id_espaco_seq; Type: SEQUENCE SET; Schema: reservas; Owner: postgres
--

SELECT pg_catalog.setval('reservas.espacos_id_espaco_seq', 4, true);


--
-- TOC entry 4930 (class 0 OID 0)
-- Dependencies: 218
-- Name: moradores_id_morador_seq; Type: SEQUENCE SET; Schema: reservas; Owner: postgres
--

SELECT pg_catalog.setval('reservas.moradores_id_morador_seq', 4, true);


--
-- TOC entry 4764 (class 2606 OID 16695)
-- Name: agenda_reservas agenda_reservas_id_espaco_data_reserva_horario_key; Type: CONSTRAINT; Schema: reservas; Owner: postgres
--

ALTER TABLE ONLY reservas.agenda_reservas
    ADD CONSTRAINT agenda_reservas_id_espaco_data_reserva_horario_key UNIQUE (id_espaco, data_reserva, horario);


--
-- TOC entry 4766 (class 2606 OID 16693)
-- Name: agenda_reservas agenda_reservas_pkey; Type: CONSTRAINT; Schema: reservas; Owner: postgres
--

ALTER TABLE ONLY reservas.agenda_reservas
    ADD CONSTRAINT agenda_reservas_pkey PRIMARY KEY (id_reserva);


--
-- TOC entry 4760 (class 2606 OID 16667)
-- Name: espacos espacos_nome_key; Type: CONSTRAINT; Schema: reservas; Owner: postgres
--

ALTER TABLE ONLY reservas.espacos
    ADD CONSTRAINT espacos_nome_key UNIQUE (nome);


--
-- TOC entry 4762 (class 2606 OID 16665)
-- Name: espacos espacos_pkey; Type: CONSTRAINT; Schema: reservas; Owner: postgres
--

ALTER TABLE ONLY reservas.espacos
    ADD CONSTRAINT espacos_pkey PRIMARY KEY (id_espaco);


--
-- TOC entry 4758 (class 2606 OID 16657)
-- Name: moradores moradores_pkey; Type: CONSTRAINT; Schema: reservas; Owner: postgres
--

ALTER TABLE ONLY reservas.moradores
    ADD CONSTRAINT moradores_pkey PRIMARY KEY (id_morador);


--
-- TOC entry 4767 (class 2606 OID 16701)
-- Name: agenda_reservas agenda_reservas_id_espaco_fkey; Type: FK CONSTRAINT; Schema: reservas; Owner: postgres
--

ALTER TABLE ONLY reservas.agenda_reservas
    ADD CONSTRAINT agenda_reservas_id_espaco_fkey FOREIGN KEY (id_espaco) REFERENCES reservas.espacos(id_espaco);


--
-- TOC entry 4768 (class 2606 OID 16696)
-- Name: agenda_reservas agenda_reservas_id_morador_fkey; Type: FK CONSTRAINT; Schema: reservas; Owner: postgres
--

ALTER TABLE ONLY reservas.agenda_reservas
    ADD CONSTRAINT agenda_reservas_id_morador_fkey FOREIGN KEY (id_morador) REFERENCES reservas.moradores(id_morador);


-- Completed on 2025-07-09 14:27:40

--
-- PostgreSQL database dump complete
--
-- Consulta Fácil: todos os espaços com suas capacidades
SELECT nome, capacidade_maxima
FROM reservas.espacos;

-- Consulta Intermediária: reservas feitas por um morador específico (ex: Ana Silva)
SELECT m.nome_completo, e.nome AS espaco, a.data_reserva, a.horario
FROM reservas.agenda_reservas a
JOIN reservas.moradores m ON a.id_morador = m.id_morador
JOIN reservas.espacos e ON a.id_espaco = e.id_espaco
WHERE m.nome_completo = 'Ana Silva';

-- Consulta Difícil: reservas do Salão de Festas em julho de 2025, ordenadas por data
SELECT m.nome_completo, a.data_reserva, a.horario
FROM reservas.agenda_reservas a
JOIN reservas.moradores m ON a.id_morador = m.id_morador
JOIN reservas.espacos e ON a.id_espaco = e.id_espaco
WHERE e.nome = 'Salão de Festas'
  AND EXTRACT(MONTH FROM a.data_reserva) = 7
  AND EXTRACT(YEAR FROM a.data_reserva) = 2025
ORDER BY a.data_reserva, a.horario;

