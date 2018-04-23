open Utils;

requireCSS("src/reset.css");

type route =
  | Comments(int)
  | List(string, int);

type state = {route};

type action =
  | ChangeRoute(route);

let reducer = (action, _state) =>
  switch action {
  | ChangeRoute(route) => ReasonReact.Update({route: route})
};

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch url.path {
  | [] => List("top", 1)
  | ["top", page] => List("top", int_of_string(page))
  | ["news", page] => List("news", int_of_string(page))
  | ["show", page] => List("show", int_of_string(page))
  | ["ask", page] => List("ask", int_of_string(page))
  | ["jobs", page] => List("jobs", int_of_string(page))
  | ["item", id] => Comments(int_of_string(id))
  | _ => List("top", 1) /* todo 404 */
  | ["about"] => List("top", 1) /* todo about */
};

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  reducer,
  initialState: () => {route: List("top", 1)},
  subscriptions: (self) => [
    Sub(
      () => ReasonReact.Router.watchUrl((url) => self.send(ChangeRoute(url |> mapUrlToRoute))),
      ReasonReact.Router.unwatchUrl
    )
  ],
  render: (self) =>
  (
    switch self.state.route {
    | Comments(id) => <CommentsPage id />
    | List(storyType, page) => <List storyType page max={5} />
    }
  )
};
