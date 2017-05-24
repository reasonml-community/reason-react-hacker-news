open Utils;

registerServiceWorker ();

let renderForRoute route => ReactDOMRe.renderToElementWithId <App route /> "root";

let router =
  DirectorRe.makeRouter {
    "/": fun () => renderForRoute Routing.Home,
    "/comments/:id": fun (id: string) => renderForRoute (Routing.Comments (int_of_string id))
  };

DirectorRe.init router "/";
