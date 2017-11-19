open Utils;

registerServiceWorker();

let renderForRoute = (route) => ReactDOMRe.renderToElementWithId(<App route />, "root");

let router =
  DirectorRe.makeRouter({
    "/": () => renderForRoute(Routing.Home),
    "/comments/:id": (id: string) => renderForRoute(Routing.Comments(int_of_string(id)))
  });

DirectorRe.init(router, "/");
