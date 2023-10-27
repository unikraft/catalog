/*******************************************************************************
   Chinook Database - Version 1.4
   Script: Chinook_Sqlite.sql
   Description: Creates and populates the Chinook database.
   DB Server: Sqlite
   Author: Luis Rocha
   License: http://www.codeplex.com/ChinookDatabase/license
********************************************************************************/

/*******************************************************************************
   Drop Tables
********************************************************************************/
DROP TABLE IF EXISTS [Album];

DROP TABLE IF EXISTS [Artist];

/*******************************************************************************
   Create Tables
********************************************************************************/
CREATE TABLE [Album]
(
    [AlbumId] INTEGER  NOT NULL,
    [Title] NVARCHAR(160)  NOT NULL,
    [ArtistId] INTEGER  NOT NULL,
    CONSTRAINT [PK_Album] PRIMARY KEY  ([AlbumId]),
    FOREIGN KEY ([ArtistId]) REFERENCES [Artist] ([ArtistId]) 
		ON DELETE NO ACTION ON UPDATE NO ACTION
);

CREATE TABLE [Artist]
(
    [ArtistId] INTEGER  NOT NULL,
    [Name] NVARCHAR(120),
    CONSTRAINT [PK_Artist] PRIMARY KEY  ([ArtistId])
);

/*******************************************************************************
   Create Primary Key Unique Indexes
********************************************************************************/

/*******************************************************************************
   Create Foreign Keys
********************************************************************************/
CREATE INDEX [IFK_AlbumArtistId] ON [Album] ([ArtistId]);

/*******************************************************************************
   Populate Tables
********************************************************************************/
INSERT INTO [Artist] ([ArtistId], [Name]) VALUES (1, 'AC/DC');
INSERT INTO [Artist] ([ArtistId], [Name]) VALUES (2, 'Accept');
INSERT INTO [Artist] ([ArtistId], [Name]) VALUES (3, 'Aerosmith');
INSERT INTO [Artist] ([ArtistId], [Name]) VALUES (4, 'Alanis Morissette');
INSERT INTO [Artist] ([ArtistId], [Name]) VALUES (5, 'Alice In Chains');
INSERT INTO [Artist] ([ArtistId], [Name]) VALUES (6, 'Antônio Carlos Jobim');
INSERT INTO [Artist] ([ArtistId], [Name]) VALUES (7, 'Apocalyptica');
INSERT INTO [Artist] ([ArtistId], [Name]) VALUES (8, 'Audioslave');
INSERT INTO [Artist] ([ArtistId], [Name]) VALUES (9, 'BackBeat');
INSERT INTO [Artist] ([ArtistId], [Name]) VALUES (10, 'Billy Cobham');

INSERT INTO [Album] ([AlbumId], [Title], [ArtistId]) VALUES (1, 'For Those About To Rock We Salute You', 1);
INSERT INTO [Album] ([AlbumId], [Title], [ArtistId]) VALUES (2, 'Balls to the Wall', 2);
INSERT INTO [Album] ([AlbumId], [Title], [ArtistId]) VALUES (3, 'Restless and Wild', 2);
INSERT INTO [Album] ([AlbumId], [Title], [ArtistId]) VALUES (4, 'Let There Be Rock', 1);
INSERT INTO [Album] ([AlbumId], [Title], [ArtistId]) VALUES (5, 'Big Ones', 3);
INSERT INTO [Album] ([AlbumId], [Title], [ArtistId]) VALUES (6, 'Jagged Little Pill', 4);
INSERT INTO [Album] ([AlbumId], [Title], [ArtistId]) VALUES (7, 'Facelift', 5);
INSERT INTO [Album] ([AlbumId], [Title], [ArtistId]) VALUES (8, 'Warner 25 Anos', 6);
INSERT INTO [Album] ([AlbumId], [Title], [ArtistId]) VALUES (9, 'Plays Metallica By Four Cellos', 7);
INSERT INTO [Album] ([AlbumId], [Title], [ArtistId]) VALUES (10, 'Audioslave', 8);
INSERT INTO [Album] ([AlbumId], [Title], [ArtistId]) VALUES (11, 'Out Of Exile', 8);
INSERT INTO [Album] ([AlbumId], [Title], [ArtistId]) VALUES (12, 'BackBeat Soundtrack', 9);
INSERT INTO [Album] ([AlbumId], [Title], [ArtistId]) VALUES (13, 'The Best Of Billy Cobham', 10);
