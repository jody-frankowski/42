const auth = require('koa-basic-auth');
const cors = require('@koa/cors');
const createRouter = require('koa-bestest-router');
const Koa = require('koa');
const koaBody = require('koa-body');
const mount = require('koa-mount');
const rewrite = require('koa-rewrite');
const serve = require('koa-static');
const session = require('koa-session');
const sqlite = require('sqlite');

ADMIN_PORT = 4242;
CLIENT_PORT = 3000;

ALLOWED_LANGUAGES = [
					'PHP',
					'Html',
					'CSS',
					'Javascript',
					'C++',
					'Python',
					'Ruby',
];

(async () => {
	async function setupDb() {
		try {
			await db.run('CREATE TABLE pastes (\
						id TEXT,\
						author TEXT,\
						title TEXT,\
						content TEXT,\
						language TEXT,\
						insertion_date INTEGER,\
						expiration_date INTEGER,\
						num_views INTEGER,\
						max_views INTEGER,\
						public INTEGER\
						);');
		} catch {
		}

	}
	const dbPromise = sqlite.open("db.sqlite", { Promise });

	const db = await dbPromise;
	await setupDb();

	let timerId = setInterval(() => clearExpiredPastes(), 60000);

	async function deleteContentOf(id) {
		const query = await db.prepare("UPDATE pastes SET content = '' WHERE id = (?)");
		await query.run(id);
	}

	async function clearExpiredPastes() {
		const query = await db.prepare("SELECT id, expiration_date FROM pastes WHERE content != ''");

		var row;
		while((row = await query.get()))
		{
			if (row.expiration_date != -1 && Date.now() > row.expiration_date)
			{
				console.error(`Deleting expired: ${row.id}`);
				await deleteContentOf(row.id);
			}
		}
		await query.finalize();
	}

	function generateId() {
		return Math.random().toString(32).substring(2);
	}

	async function generateUniqueId() {
		const query = await db.prepare("SELECT COUNT(*) AS Count FROM pastes WHERE id = (?)");
		do {
			id = generateId();
			count = (await query.all(id))[0].Count;
		} while (count != 0)

		return id;
	}

	async function incrementViews(id)
	{
		const query = await db.prepare("UPDATE pastes SET num_views = num_views + 1 WHERE id = (?)");
		await query.run(id);
	}

	async function handleGetAll(ctx, next) {
		const query = await db.prepare("SELECT * FROM pastes");
		const data = await query.all();
		ctx.status = 200;
		ctx.body = data;
		await next();
	}

	async function handleDeletePaste(ctx, next) {
		const query = await db.prepare("UPDATE pastes SET content = '' WHERE id = (?) AND content != ''");
		const data = await query.run(ctx.params.id);

		if (data.stmt.changes == 1)
			ctx.status = 200;
		else
			ctx.status = 204;

		await next();
	}

	async function handleUpdatePaste(ctx, next) {
		try {
			var values = setValues(ctx.request.body);
		} catch(e) {
			ctx.status = 400;
			await next();
			return ;
		}

		const query = await db.prepare("UPDATE pastes SET \
											author = (?), \
											title = (?), \
											content = (?), \
											max_views = (?), \
											public = (?) \
											WHERE id = (?)");
		const data = await query.run(
			values.author,
			values.title,
			values.content,
			values.max_views,
			values.public,
			ctx.params.id
		);

		ctx.status = 302;
		ctx.set('Location', ctx.origin + '/');

		await next();
	}

	async function handleGetPaste(ctx, next) {
		const query = await db.prepare("SELECT * FROM pastes WHERE id = (?)");
		const data = await query.all(ctx.params.id);
		if (data.length > 0)
		{
			ctx.status = 200;
			if ((data[0].max_views == -1 || data[0].num_views < data[0].max_views) &&
				(data[0].expiration_date == -1 || Date.now() < data[0].expiration_date) && data[0].content.length > 0)
			{
				ctx.body = data[0];
				incrementViews(ctx.params.id);
			}
			else
			{
				ctx.body = "Can't see anymore!";
			}
		}
		else
		{
			ctx.status = 404;
		}
		await next();
	}

	async function handleGetLatest(ctx, next) {
		const query = await db.prepare("SELECT id, author, title, language, insertion_date FROM pastes WHERE public = 1 ORDER BY rowid DESC LIMIT 8");
		const data = await query.all();

		ctx.status = 200;
		ctx.body = data;
		await next();
	}

	function setValues(body) {
		var values = {
			author: body['author'],
			title: body['title'],
			content: body['content'],
			language: body['language'],
			expiration_date: body['expiration_date'],
			max_views: body['max_views'],
			public: body['public'],
		};

		if (values.content === undefined || values.content.length < 1)
		{
			throw new Error('Whoops!');
			return ;
		}

		if (values.author === undefined || values.author.length < 1)
			values.author = "Anonymous";
		if (values.title === undefined || values.title.length < 1)
			values.title = "Untitled";
		if (values.language === undefined || ALLOWED_LANGUAGES.indexOf(values.language) == -1)
			values.language = "None";
		values.insertion_date = Date.now();
		switch (values.expiration_date) {
			case "1m":
				values.expiration_date = values.insertion_date + 60*1000;
				break ;
			case "1h":
				values.expiration_date = values.insertion_date + 60*60*1000;
				break ;
			case "1d":
				values.expiration_date = values.insertion_date + 24*60*60*1000;
				break ;
			default:
				values.expiration_date = -1;
		}
		if (values.max_views === undefined || isNaN(parseInt(values.max_views)) || parseInt(values.max_views) < 1)
			values.max_views = -1;
		if (values.public === undefined)
			values.public = 1;
		else if (values.public != 0 && values.public != 1)
			values.public = 0;

		return values;
	}

	async function handlePostPaste(ctx, next) {
		// We answer 404 when there is some missing parameters
		// https://stackoverflow.com/a/3050624

		if (ctx.session.isNew) {
			ctx.status = 403;
			await next();
			return ;
		}

		try {
			var values = setValues(ctx.request.body);
		} catch(e) {
			ctx.status = 404;
			await next();
			return ;
		}

		values.id = await generateUniqueId();

		var stmt = await db.prepare("INSERT INTO pastes (\
														id,\
														author,\
														title,\
														content,\
														language,\
														insertion_date,\
														expiration_date,\
														num_views,\
														max_views,\
														public\
														) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
		await stmt.run(
						values.id,
						values.author,
						values.title,
						values.content,
						values.language,
						values.insertion_date,
						values.expiration_date,
						0,
						values.max_views,
						values.public
					  );

		ctx.status = 302;
		ctx.set('Location', ctx.origin + '/' + values.id);
		await next();
	}

	function checkOriginAgainstWhitelist(ctx) {
 		const requestOrigin = ctx.headers.origin;
 		if (!whitelist.includes(requestOrigin)) {
			console.error(`Bad origin: ${requestOrigin}`);
 			return ctx.throw(403, `${requestOrigin} is not a valid origin`);
 		}
		return requestOrigin;
	}

	const whitelist = ['http://localhost', 'http://localhost:3000', 'http://localhost:4242', 'http://192.168.33.10', 'http://192.168.33.10:3000', 'http://192.168.33.10:4242', ];

	const clientApi = new Koa();
	clientApi.use(cors({origin: checkOriginAgainstWhitelist}));
	clientApi.use(koaBody());
	// TODO
	// Ces deux routes devront renvoyer le bon code d’erreur HTTP si une méthode
	// non autorisée est utilisée pour accéder à l’une des routes.
	const clientApiRouterMiddleware = createRouter({
		GET: {
			'/paste/latest': handleGetLatest,
			'/paste/:id':    handleGetPaste,
		},
		POST: {
			'/paste': handlePostPaste,
		}
	}, true);
	clientApi.use(clientApiRouterMiddleware);

	const client = new Koa();
	client.keys = ['oaz3boh1lezahGhu'];
	client.use(session(client));
	client.use(async function (ctx, next) {
		ctx.session.activate = true;
		await next();
	});

	client.use(mount('/api', clientApi));
	client.use(rewrite('/:id', '/paste.html'));
	client.use(rewrite('/', '/index.html'));
	client.use(serve('./statics/client'));

	client.listen(CLIENT_PORT);

	const adminApi = new Koa();
	adminApi.use(koaBody());
	const adminApiRouterMiddleware = createRouter({
		DELETE: {
			'/paste/:id': handleDeletePaste,
		},
		GET: {
			'/paste/all':    handleGetAll,
		},
		POST: {
			'/paste/update/:id': handleUpdatePaste,
		},
	}, true);
	adminApi.use(adminApiRouterMiddleware);

	const admin = new Koa();
	admin.use(auth({ name: 'admin', pass: 'admin' }));
	admin.use(serve('./statics/admin'));
	admin.use(mount('/api', adminApi));
	admin.listen(ADMIN_PORT);
})();
